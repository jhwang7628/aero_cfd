#include "streamsound.h"
#include <iostream>
#include <cmath>
#include "parameters.h"
#include "ObjectLoader.h"
#include "FrameExporter.h"

using namespace std; 

MyPortaudioClass::MyPortaudioClass(vector<const SourceFunction*> allSF) : _allSF(allSF), 
                                                            _thisSF(_allSF.begin()),
                                                            _timeStamp(0), 
                                                            _globalAbsMax(0.0), 
                                                            _extraScaling(1.0), 
                                                            _prevScale(1.0),
                                                            _currScale(1.0), 
                                                            _frequencyShift(false)

{
    _data = new stereo(); 

    fp = fopen("out/log.txt", "w");

    //syncSF(); 
    computeGlobalMax();
    //printf("MyPortaudioClass instantiated. left_phase = %f, right_phase = %f\n", _data->left_phase, _data->right_phase); 
    //printf("how many source function do I have now? %lu\n", _allSF.size()); 
}


int MyPortaudioClass::myMemberCallback(const void *input, void *output,
                                       unsigned long frameCount,
                                       const PaStreamCallbackTimeInfo* timeInfo,
                                       PaStreamCallbackFlags statusFlags)
{

    float *out = (float*) output; 

    (void) timeInfo;
    (void) statusFlags; 
    (void) input; 




    if (1)
    {
        double time = timeInfo->outputBufferDacTime; 
        printf("Exporting frame at time = %f\n", time);
        FrameExporter::writeMotionCaptureData(sndState::handData, time); 
    }


    /* Copy the hand data */
    if (sndState::handData.tipVel.norm() == handData.tipVel.norm())
        curRepeatNumBuffer ++; 
    else 
        curRepeatNumBuffer = 0; 

    if (curRepeatNumBuffer > PARAMETERS::maxRepeatNumBuffer)
    {
        for (int ii=0; ii<frameCount; ii++) 
        {
            *out++ = 0.0f; 
            *out++ = 0.0f;  

        }
        return paContinue; 
    }



    handData = sndState::handData; 


    Eigen::Vector3d wind_ref = handData.R_w2o * (-handData.tipVel);
    wind_ref.normalize();
    wind_ref[1] = 0.0; // project it to 2D plane.

    // compute nearest sound state
    double theta;
    if (wind_ref.norm() > 1E-14)
        theta = acos(wind_ref[0] / wind_ref.norm()); // 
    else // probably haven't got any mocap data
        theta = 0.0; 

    //int interval = ((theta*180.0/3.14159) % (*_thisSF)->wrapAngle) / (*_thisSF)->sampleAngle; 
    //
    int wrapAngle = _allSF.size() * ObjectLoader::sampleInterval;
    int textureIndex =  ( (int)floor(theta*180.0/3.14159) % wrapAngle ) / ObjectLoader::sampleInterval;

    //printf("texture # %u is used\n", (*_thisSF)->getTextureIndex()); 

    _thisSF = _allSF.begin() + textureIndex;

    //printf("sound source function # %u is used\n", textureIndex);


    /* make sure the mouse speed is frozen between every callback. */

    _prevScale = _currScale;
    //_currScale = sndState::currMouseSpeed/4.0;
    _currScale = sndState::currMouseSpeed/_eng->getSensitivity();
    double alpha; 
    double scale; //blended scales
    double sharpness = _eng->getSharpness(); 

    unsigned int ii; 

    for (ii=0; ii<frameCount; ii++) 
    {
        alpha = (double)(ii)/(double)(frameCount); 
        scale = (1.0 - alpha)*_prevScale + alpha*_currScale; 

        _data->gx = (*_thisSF)->getgx(_timeStamp); 
        _data->gy = (*_thisSF)->getgy(_timeStamp); 
        _data->gz = (*_thisSF)->getgz(_timeStamp); 

        _data->left_phase =  (_data->gx + _data->gy + _data->gz)/_globalAbsMax*pow(scale,sharpness); 
        _data->right_phase = _data->left_phase; 

        /* time step the signal */
        int incre = round((double)PARAMETERS::UPSAMPLE_RATIO*scale); 

        if (_frequencyShift)
            _timeStamp += incre;
        else 
            _timeStamp += PARAMETERS::UPSAMPLE_RATIO;


        _timeStamp = _timeStamp % (*_thisSF)->maxTimeStep; 

        fprintf(fp, "%.12f %.12f\n", sndState::currMouseSpeed, _data->left_phase); 

        *out++ = (float) _data->left_phase; 
        *out++ = (float) _data->right_phase; 

    }


      
    return paContinue;
}


inline void MyPortaudioClass::toggleFrequencyShift()
{
    _frequencyShift = ! _frequencyShift;
}

inline bool MyPortaudioClass::getFrequencyShift()
{
    return _frequencyShift;
}



/////////////////////////////////////////////////////////

void Engine::InitStream()
{
    cout << " - Initialize stream. " << endl; 
    _err = Pa_Initialize();

    if (_err != paNoError)
        printf("Cannot initialize stream. %s\n", Pa_GetErrorText(_err)); 

}


void Engine::OpenStream()
{
    cout << " - Open stream. " << endl; 

    if (NULL == _mypa)
    {
        cout << "   - Initializing MyPortaudioClass. " <<endl; 
        _mypa = new MyPortaudioClass(_allSF); 
        _mypa->setEng(this); 
    }

    _outputParameters.device = Pa_GetDefaultOutputDevice(); 

    if (_outputParameters.device == paNoDevice) 
    {
        printf("**Error: No deafult output device.\n"); 
        return;
    }

    _outputParameters.channelCount = 2; 
    _outputParameters.sampleFormat = paFloat32; 
    _outputParameters.suggestedLatency = Pa_GetDeviceInfo(_outputParameters.device)->defaultLowOutputLatency; 
    _outputParameters.hostApiSpecificStreamInfo = NULL; 

    _err = Pa_OpenStream(
               &_stream,
               NULL, /* no input */
               &_outputParameters,
               10000, /* SAMPLE_RATE, */ 
               //paFramesPerBufferUnspecified, /* FRAMES_PER_BUFFER, */
               100, /* FRAMES_PER_BUFFER, */
               paClipOff,      /* we won't output out of range samples so don't bother clipping them */
               &(MyPortaudioClass::myPaCallback),
               (void*) _mypa);

    if (_err != paNoError)
    {
        printf("**Error: Cannot start stream. %s\n", Pa_GetErrorText(_err)); 
        return;
    }
    else 
    {
        cout << "   - Stream opened successfully." << endl; 
    }


    //Pa_OpenDefaultStream(&_stream,
    //        0,          /* no input channels */
    //        2,          /* stereo output */
    //        paFloat32,  /* 32 bit floating point output */
    //        10000,      /* Sampling rate */
    //        256,        /* frames per buffer, i.e. the number
    //                       of sample frames that PortAudio will
    //                       request from the callback. Many apps
    //                       may want to use paFramesPerBufferUnspecified, which
    //                       tells PortAudio to pick the best,
    //                       possibly changing, buffer size.*/
    //        &(MyPortaudioClass::myPaCallback), /* this is your callback function */
    //        (void*) _mypa); /*This is a pointer that will be passed to your callback*/
    //if (NULL != _stream) 
    //    cout << "   - Stream opened successfully." << endl; 
}

void Engine::StartStream()
{
    cout << " - Start stream. " << endl; 
    if (NULL != _stream)
    { 
        _streamStarted = true; 
        _err = Pa_StartStream(_stream);
    }

    if (_err != paNoError)
        printf("Cannot start stream. %s\n", Pa_GetErrorText(_err)); 

    cout << "   - Stream started successfully. " << endl;
}

void Engine::StopStream()
{
    cout << " - Stop stream. " << endl; 
    if (NULL != _stream && _streamStarted) 
        _err = Pa_StopStream(_stream);

    if (_err != paNoError)
        printf("Cannot stop stream. %s\n", Pa_GetErrorText(_err)); 
}


void Engine::CloseStream()
{
    cout << " - Close stream. " << endl; 
    if (NULL != _stream) 
        _err = Pa_CloseStream(_stream); 

    if (_err != paNoError)
        printf("Cannot close stream. %s\n", Pa_GetErrorText(_err)); 
}

void Engine::setExtraScaling(const double scale)
{
    _mypa->pasetExtraScaling(scale);
}

void Engine::addSF(const SourceFunction * sf)
{
    printf(" - Adding source function to audio engine : \n");
    printf("   - Object name : \"%s\"\n", sf->getShapeName());
    printf("   - Base speed  : %f\n", sf->getBaseSpeed()); 

    _allSF.push_back(sf); 

}

void Engine::toggleFrequencyShift()
{
    _mypa->toggleFrequencyShift(); 
    cout << "Frequency Shift: " << _mypa->getFrequencyShift() << endl;
}

void Engine::setGUIs(AudioGUI * agui, VisualGUI * vgui) 
{
    _agui = agui; 
    _vgui = vgui; 
}

double Engine::getSensitivity()
{
    return _agui->getSensitivity();
}

double Engine::getSharpness()
{
    return _agui->getSharpness(); 
}

///////////////////////////////////////////////////
  
  
  
double sndState::currMouseSpeed = 0.0; 
double sndState::prevMouseSpeed = 0.0; 
HandData sndState::handData;


