#ifndef PARAMETERS_H
#define PARAMETERS_H

class PARAMETERS {

    public : 

    /* linear interpolation level */
    static const int UPSAMPLE_RATIO = 10;

    /* bufferzone for mouse speed detection, measured in pixels */
    static const int BUFFERZONE = 50; 

    /* if the speed doesn't change within this number of callback, mute it. (This is a quick hack to solve the out-of-bounds playback problem) */
    static const int maxRepeatNumBuffer = 10; 

    /* read motion capture data from hard drive */
    static const bool SAVE_MOCAP_TO_DRIVE = false;

    /* read motion capture data from hard drive */
    static const bool READ_MOCAP_FROM_DRIVE = false;
};



#endif 
