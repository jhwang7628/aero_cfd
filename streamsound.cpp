#include "streamsound.h"
#include <iostream>

using namespace std; 

int MyPortaudioClass::myMemberCallback(const void *input, void *output,
                                       unsigned long frameCount,
                                       const PaStreamCallbackTimeInfo* timeInfo,
                                       PaStreamCallbackFlags statusFlags)
{

    // Do what you need (having access to every part of MyPortaudioClass)
    return paContinue;
}
