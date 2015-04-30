#ifndef STREAMSOUND_H
#define STREAMSOUND_H

#include <stdio.h>
#include <iostream>
#include <vector>
#include <math.h>

#include "ui_window.h"
#include <QtGui>

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
    double _globalAbsMax; 
    double _extraScaling; 

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

    /* 
     * Move the time stamp dt unit further; if dt not specified step 1 unit.
     */
    void timeStep(int dt);
    void timeStep(); 

    inline void computeGlobalMax()
    {
        for (const SourceFunction * sf : _allSF)
            _globalAbsMax = max(sf->getmax(), _globalAbsMax); 
    }
    inline void pasetExtraScaling(const double scale)
    {
        _extraScaling = scale;
    }
    inline void computePhase()
    {
        _data->left_phase =  (_data->gx + _data->gy + _data->gz)/_globalAbsMax*_extraScaling; 
        //cout << "scale : " << _extraScaling/_globalAbsMax << endl;
        //_data->right_phase = (_data->gx + _data->gy + _data->gz)/_globalAbsMax/_extraScaling; 
        _data->right_phase = _data->left_phase; 
    }

    inline void syncSF()
    {
        _data->gx = (*_thisSF)->getgx(_timeStamp); 
        _data->gy = (*_thisSF)->getgy(_timeStamp); 
        _data->gz = (*_thisSF)->getgz(_timeStamp); 
    }





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

    void setExtraScaling(const double scale);
    void addSF(const SourceFunction * sf);

}; 


#endif
