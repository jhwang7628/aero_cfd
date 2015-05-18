#include "ObjectLoader.h" 
#include "streamsound.h" 
#include <string>
#include <Eigen/Dense>
#include "IO/IO.h"
#include "auxFunc.h"

int ObjectLoader::sampleInterval = 5;

void ObjectLoader::loadCylinder(Engine & eng)
{
    string filename = string("./sound/test/g.dat"); 
    
    Eigen::MatrixXd * sound  = new Eigen::MatrixXd(); 
    IO::readMatrixXd(*sound, filename.c_str(), BINARY); 
    SourceFunction * sf = new SourceFunction(10, cylinder, sound, 0);
    eng.addSF(sf); 
}

void ObjectLoader::loadCylinderv30(Engine & eng) 
{
    string filename = string("./sound/cylinder/g_2Dcylinder_v30.dat"); 
    
    Eigen::MatrixXd * sound  = new Eigen::MatrixXd(); 
    IO::readMatrixXd(*sound, filename.c_str(), BINARY); 
    SourceFunction * sf = new SourceFunction(10, cylinder, sound, 0);
    eng.addSF(sf); 
}

void ObjectLoader::loadCylinderv45(Engine & eng) 
{
    string filename = string("./sound/cylinder/g_2Dcylinder_v45.dat"); 
    
    Eigen::MatrixXd * sound  = new Eigen::MatrixXd(); 
    IO::readMatrixXd(*sound, filename.c_str(), BINARY); 
    SourceFunction * sf = new SourceFunction(10, cylinder, sound, 0);
    eng.addSF(sf); 
}

void ObjectLoader::loadCylinderRepeat(Engine & eng)
{
    for (int ii=0; ii<=9; ii++)
    {
        string filename = string("./sound/test/g.dat"); 

        Eigen::MatrixXd * sound  = new Eigen::MatrixXd(); 
        //SoundReader::wavreader("./sound/test.wav", 20000, sound); 
        IO::readMatrixXd(*sound, filename.c_str(), BINARY); 
        SourceFunction * sf = new SourceFunction(10, cylinder, sound, ii);
        eng.addSF(sf); 
    }
}


void ObjectLoader::loadSquare(Engine & eng)
{
    for (int ii=0; ii<=9; ii++)
    {
        string num = to_string(ii*ObjectLoader::sampleInterval); 
        string filename = string("./sound/square/g_2Dsquare_ascii_y") + num + ".dat"; 

        Eigen::MatrixXd * sound  = new Eigen::MatrixXd(); 
        //SoundReader::wavreader("./sound/test.wav", 20000, sound); 
        IO::readMatrixXd(*sound, filename.c_str(), BINARY); 
        SourceFunction * sf = new SourceFunction(10, square, sound, ii);
        eng.addSF(sf); 
    }
}


void ObjectLoader::loadSword(Engine & eng)
{
    for (int ii=0; ii<=36; ii++)
    {
        string num = to_string(ii*ObjectLoader::sampleInterval); 
        string filename = string("./sound/sword_aniso/g_2Dsword_aniso_ascii_y") + num + ".dat"; 

        Eigen::MatrixXd * sound  = new Eigen::MatrixXd(); 
        //SoundReader::wavreader("./sound/test.wav", 20000, sound); 
        IO::readMatrixXd(*sound, filename.c_str(), BINARY); 
        SourceFunction * sf = new SourceFunction(10, sword_aniso, sound, ii);
        eng.addSF(sf); 
    }
}

