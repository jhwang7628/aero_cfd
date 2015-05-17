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

class Engine;
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

    Engine * _eng;

    int _timeStamp;
    double _globalAbsMax; 
    double _extraScaling; 
    double _prevScale; 
    double _currScale;
    bool _frequencyShift;

    public : 


    FILE*fp; 

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

    inline void computeGlobalMax()
    {
        for (const SourceFunction * sf : _allSF)
            _globalAbsMax = max(sf->getmax(), _globalAbsMax); 
    }
    inline void pasetExtraScaling(const double scale)
    {
        _extraScaling = scale;
    }

    inline void toggleFrequencyShift(); 
    inline bool getFrequencyShift();

    void setEng(Engine * eng) 
    {
        _eng = eng; 
    }


};

class VisualGUI; 
class AudioGUI;

class Engine
{

    PaStreamParameters _outputParameters; 
    PaStream * _stream;
    PaError _err; 
    vector<const SourceFunction*> _allSF; 
    MyPortaudioClass * _mypa; 
    AudioGUI * _agui; 
    VisualGUI * _vgui; 

    

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

    void toggleFrequencyShift(); 

    void setGUIs(AudioGUI * agui, VisualGUI * vgui); 
    void computeMouseSpeed();
    double getSensitivity(); 
    double getSharpness(); 


}; 

/* Store some useful sndstate parameters */
class sndState
{
    public : 
        static double currMouseSpeed; 
        static double prevMouseSpeed;


}; 


#endif
