#include "streamsound.h"
#include <iostream>

using namespace std; 

MyPortaudioClass::MyPortaudioClass(vector<const SourceFunction*> allSF) : _allSF(allSF), 
                                                            _thisSF(_allSF.begin()),
                                                            _timeStamp(0), 
                                                            globalAbsMax(0.0)
    {
        _data = new stereo(); 

        syncSF(); 
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

    unsigned int ii; 
    for (ii=0; ii<frameCount; ii++) 
    {

        *out++ = (float) _data->left_phase; 
        *out++ = (float) _data->right_phase; 

        computePhase();
        timeStep(); 

    }
    
    
    //_data->outTime = timeInfo->outputBufferDacTime;
    //printf("----------------------\n"); 
    //printf("g = %f, %f, %f at time = %f\n", _data->gx, _data->gy, _data->gz, _data->outTime); 
    //printf("left_phase = %f, right_phase = %f\n", _data->left_phase, _data->right_phase); 
    //printf("globalAbsMax = %f\n", globalAbsMax); 

    // Do what you need (having access to every part of MyPortaudioClass)
      
      
    return paContinue;
}

inline void MyPortaudioClass::computeGlobalMax()
{
    for (const SourceFunction * sf : _allSF)
        globalAbsMax = max(sf->getmax(), globalAbsMax); 
}

inline void MyPortaudioClass::timeStep(int dt)
{
    _timeStamp += dt; 
    if (_timeStamp >= (*_thisSF)->maxTimeStep)
        _timeStamp = _timeStamp - (*_thisSF)->maxTimeStep; 

    syncSF(); 
}

inline void MyPortaudioClass::timeStep()
{
    timeStep(1);
}

inline void MyPortaudioClass::syncSF()
{
    _data->gx = (*_thisSF)->getgx(_timeStamp); 
    _data->gy = (*_thisSF)->getgy(_timeStamp); 
    _data->gz = (*_thisSF)->getgz(_timeStamp); 
}

inline void MyPortaudioClass::computePhase()
{
    _data->left_phase =  (_data->gx + _data->gy + _data->gz)/globalAbsMax; 
    _data->right_phase = (_data->gx + _data->gy + _data->gz)/globalAbsMax; 
}



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
    }

    Pa_OpenDefaultStream(&_stream,
            0,          /* no input channels */
            2,          /* stereo output */
            paFloat32,  /* 32 bit floating point output */
            10000,      /* Sampling rate */
            256,        /* frames per buffer, i.e. the number
                           of sample frames that PortAudio will
                           request from the callback. Many apps
                           may want to use paFramesPerBufferUnspecified, which
                           tells PortAudio to pick the best,
                           possibly changing, buffer size.*/
            &(MyPortaudioClass::myPaCallback), /* this is your callback function */
            (void*) _mypa); /*This is a pointer that will be passed to your callback*/
    if (NULL != _stream) 
        cout << "   - Stream opened successfully." << endl; 
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

void Engine::addSF(const SourceFunction * sf)
{
    printf(" - Adding source function to audio engine : \n");
    printf("   - Object name : \"%s\"\n", sf->getShapeName());
    printf("   - Base speed  : %f\n", sf->getBaseSpeed()); 

    _allSF.push_back(sf); 

}