#include <stdio.h>
#include <iostream>
#include <math.h>

#include "portaudio.h"
#include "pa_util.h"

using namespace std; 

class MyPortaudioClass
{

    /* Open an audio I/O stream. */
    public : 
    int myMemberCallback(const void *input, void *output,
            unsigned long frameCount,
            const PaStreamCallbackTimeInfo* timeInfo,
            PaStreamCallbackFlags statusFlags);

    static int myPaCallback(const void *input, void *output,
            unsigned long frameCount,
            const PaStreamCallbackTimeInfo* timeInfo,
            PaStreamCallbackFlags statusFlags,
            void *userData)
    {
        cout << " hello " << endl;
        return ((MyPortaudioClass*)userData)
            ->myMemberCallback(input, output, frameCount, timeInfo, statusFlags);
    }

};

class Engine
{
    PaStream *stream;
    PaError err; 

    bool _streamStarted; 

    public : 

    Engine() : _streamStarted(false) { }
    ~Engine() {}

    void OpenStream()
    {

        cout << " - Open stream. " << endl; 
        MyPortaudioClass * test = new MyPortaudioClass(); 
        if (test != NULL)
            printf("test is not NULL!!!!\n"); 
        Pa_OpenDefaultStream(&stream,
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
                &MyPortaudioClass::myPaCallback, /* this is your callback function */
                (void*) test); /*This is a pointer that will be passed to
                         your callback*/
    }

    void InitStream() 
    {
        cout << " - Initialize stream. " << endl; 
        err = Pa_Initialize();

        if (err != paNoError)
            printf("Cannot initialize stream. %s\n", Pa_GetErrorText(err)); 

    }

    void StartStream() 
    {
        cout << " - Start stream. " << endl; 
        if (NULL != stream)
        {
            _streamStarted = true; 
            cout << "   - before checkpoint." << endl; 
            err = Pa_StartStream(stream);
            cout << "   - pass checkpoint." << endl; 
        }

        if (err != paNoError)
            printf("Cannot start stream. %s\n", Pa_GetErrorText(err)); 
    }

    void StopStream() 
    {
        cout << " - Stop stream. " << endl; 
        if (NULL != stream && _streamStarted) 
            err = Pa_StopStream(stream);

        if (err != paNoError)
            printf("Cannot stop stream. %s\n", Pa_GetErrorText(err)); 
    }

    void CloseStream() 
    {
        cout << " - Close stream. " << endl; 
        if (NULL != stream) 
            err = Pa_CloseStream(stream); 

        if (err != paNoError)
            printf("Cannot close stream. %s\n", Pa_GetErrorText(err)); 
    }


}; 

