#ifndef PARAMETERS_H
#define PARAMETERS_H

class PARAMETERS {

    public : 

    static const int UPSAMPLE_RATIO = 10;
    static const int BUFFERZONE = 50; // bufferzone for mouse speed detection, measured in pixels
    static const int maxRepeatNumBuffer = 10; // if the speed doesn't change within this number of callback, mute it. (This is a quick hack to solve the out-of-bounds playback problem)
};



#endif 
