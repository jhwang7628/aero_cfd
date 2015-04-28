#include <stdio.h> 
#include <unistd.h>
#include <iostream>

#include <Eigen/Dense>

#include <sndfile.h>
#include "portaudio.h"
#include "pa_util.h"

#include "ui_window.h"
#include <qapplication.h>
#include <QtGui>
#include <QObject>

#include "readsound.h"
#include "sourcefunction.h"
#include "streamsound.h"

#include "IO/IO.h"


#define MAX_BUFFER_DOUBLE (500000)

using namespace std; 



int main(int argc, char ** argv) {

    cout  << "project starts!" << endl; 

    Eigen::MatrixXd * sound  = new Eigen::MatrixXd(); 
    //SoundReader::wavreader("./sound/test.wav", 20000, sound); 
    IO::readMatrixXd(*sound, "./sound/g.dat", BINARY); 

    SourceFunction * sf = new SourceFunction(10, cylinder, sound);
    Engine eng; 
    eng.addSF(sf); 

    cout << "Initialzing audio streaming.. " << endl; 
    eng.InitStream(); 
    eng.OpenStream(); 
    //eng.StartStream(); 

    //sleep(50);
    //eng.StopStream(); 
    //eng.CloseStream(); 





    QApplication application(argc,argv);
    GUI gui; 
    gui.setQA(&application); 
    gui.setUI(); 

    //eng.setQA(&application);
    //eng.setUI();

    Viewer viewer;

    viewer.setWindowTitle("keyboardAndMouse");

    viewer.show();


    return application.exec();



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

}
