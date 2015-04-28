#ifndef STREAMSOUND_H
#define STREAMSOUND_H

#include <stdio.h>
#include <iostream>
#include <vector>
#include <math.h>

#include "ui_window.h"
#include <qapplication.h>
#include <QtGui>
#include <QObject>

#include "portaudio.h"
#include "pa_util.h"
#include "sourcefunction.h"

using namespace std; 

class MyPortaudioClass
{
    typedef struct stereo
    {
        double left_phase; 
        double right_phase; 

        double outTime; 

        double gx; 
        double gy; 
        double gz; 

    } stereo; 

    stereo * _data;

    vector<const SourceFunction*> _allSF;
    vector<const SourceFunction*>::iterator _thisSF; 

    int _timeStamp;
    double globalAbsMax; 

    public : 

    MyPortaudioClass(vector<const SourceFunction*> allSF);

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
        return ((MyPortaudioClass*)userData)
            ->myMemberCallback(input, output, frameCount, timeInfo, statusFlags);
    }


    inline void computeGlobalMax(); 
    inline void computePhase();

    /* 
     * Move the time stamp dt unit further; if dt not specified step 1 unit.
     */
    inline void timeStep(int dt);
    inline void timeStep(); 

    void syncSF(); 

    

};

class Engine
{

    PaStream * _stream;
    PaError _err; 
    vector<const SourceFunction*> _allSF; 
    MyPortaudioClass * _mypa; 

    bool _streamStarted; 

    public : 

    Engine() : _stream(NULL), 
               _mypa(NULL), 
               _streamStarted(false) { } 

    ~Engine() {}



    void InitStream(); 
    void OpenStream(); 
    void StartStream(); 
    void StopStream();
    void CloseStream(); 

    void addSF(const SourceFunction * sf);

}; 


#endif
