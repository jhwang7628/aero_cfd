#include <stdio.h> 
#include <iostream>

#include <Eigen/Dense>
#include <sndfile.h>

#include "readsound.h"
#include "sourcefunction.h"
#include "portaudio.h"
#include "pa_util.h"
#include "streamsound.h"

#define MAX_BUFFER_DOUBLE (500000)

using namespace std; 


int main() {

    cout  << "project starts!" << endl; 

    Eigen::MatrixXd * sound = new Eigen::MatrixXd(); 
    SoundReader::wavreader("./sound/test.wav", 20000, sound); 
    SourceFunction * sf = new SourceFunction(10, cylinder, sound);

    MyPortaudioClass * test = new MyPortaudioClass(); 

    cout << "Initialzing audio streaming.. " << endl; 
    Engine eng; 
    eng.OpenStream(); 
    eng.InitStream(); 
    eng.StartStream(); 
    eng.StopStream(); 
    eng.CloseStream(); 






    //PaError err = Pa_OpenStream(
    //                            &stream,
    //                            NULL, /* no input */
    //                            &outputParameters,
    //                            SAMPLE_RATE,
    //                            FRAMES_PER_BUFFER,
    //                            paClipOff,      /* we won't output out of range samples so don't bother clipping them */
    //                            patestCallback,
    //                            &data );
    //PaError pa_error = Pa_OpenStream(
    //                                 &MyPortaudioClass::myPaCallback,  // streamCallback
    //                                 test);                            // userData

    // create opengl window to do swinging test based on mouse movement

    return 0;

}
