#include <stdio.h> 
#include <unistd.h>
#include <iostream>

#include <string>
#include <sstream>

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
#include "LeapMotion.h"
#include "ObjectLoader.h"

#include "IO/IO.h"
#include "auxFunc.h"


#define MAX_BUFFER_DOUBLE (500000)

using namespace std; 

int main(int argc, char ** argv) {

    cout  << "project starts!" << endl; 

    Engine eng; 

    /* 
     * Load the motion capture data,
     * different loader modules can be uncommented.
     * */
    eng.ReadHandDataFromDrive("mocap_data/sequence1"); 
    ObjectLoader::loadCylinder(eng);
    //ObjectLoader::loadCylinderv30(eng); 
    //ObjectLoader::loadCylinderv45(eng); 
    //ObjectLoader::loadCylinderRepeat(eng);
    //ObjectLoader::loadSquare(eng);
    //ObjectLoader::loadSword(eng);
    //ObjectLoader::loadSwordAniso(eng);

    cout << "Initialzing audio streaming.. " << endl; 
    eng.InitStream(); 
    eng.OpenStream(); 

    QApplication application(argc,argv);
    VisualGUI vgui(&eng); 
    AudioGUI  agui(&eng,&vgui); 
    eng.setGUIs(&agui, &vgui);


    return application.exec();

}
