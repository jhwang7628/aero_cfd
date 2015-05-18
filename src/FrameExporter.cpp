#include "FrameExporter.h"
#include "LeapMotion.h"
#include "auxFunc.h"
#include <string>
#include <iostream>

#include "IO/IO.h"


using namespace std; 

int FrameExporter::frame = 0;

void FrameExporter::readAllMotionCaptureData(const char * indir)
{

    //vector<string> filenames; 
    //IO::listDirectory(indir, "0", filenames); 

    //AllHandData = new vector<HandData>(); 
    //AllHandData->resize(filenames.size()); 


    //for (int ii=0; ii<filenames.size(); ii++) 
    //{
    //    string filename = string(indir) + "/" + filenames[ii]; 
    //    HandData hd; 
    //    double time; 
    //    time = readMotionCaptureData(filename.c_str(), hd); 
    //    (*AllHandData)[ii] = hd; 
    //}

}

void FrameExporter::readAllMotionCaptureData(vector<HandData> & allhd, const char * indir)
{

    vector<string> filenames; 
    IO::listDirectory(indir, "0", filenames); 

    allhd.resize(filenames.size()); 

    for (int ii=0; ii<filenames.size(); ii++) 
    {
        string filename = string(indir) + "/" + filenames[ii]; 
        HandData hd; 
        double time; 
        time = readMotionCaptureData(filename.c_str(), hd); 
        allhd[ii] = hd; 
    }

}

void FrameExporter::writeMotionCaptureData(const HandData & handData, const double time)
{


    char fpath[100]; 
    snprintf( fpath, 100, "out/frames/%.5u.handData", frame );

    //string fpath = string("out/frames/") + to_string(frame) + ".handData"; 
    FILE * fp = fopen(fpath,"w"); 


    fprintf(fp, "%.12f\n", time); 
    fprintf(fp, "%.12f %.12f %.12f\n", handData.tipPos[0] , handData.tipPos[1] , handData.tipPos[2]); 
    fprintf(fp, "%.12f %.12f %.12f\n", handData.tipVel[0] , handData.tipVel[1] , handData.tipVel[2]); 
    fprintf(fp, "%.12f %.12f %.12f\n", handData.handDir[0], handData.handDir[1], handData.handDir[2]); 
    fprintf(fp, "%.12f %.12f %.12f\n", handData.palmNor[0], handData.palmNor[1], handData.palmNor[2]); 
    //fprintf(fp, "%.12f %.12f %.12f %.12f %.12f %.12f %.12f %.12f %.12f\n", 
    //       handData.R_w2o(0,0), handData.R_w2o(0,1), handData.R_w2o(0,2), 
    //       handData.R_w2o(1,0), handData.R_w2o(1,1), handData.R_w2o(1,2), 
    //       handData.R_w2o(2,0), handData.R_w2o(2,1), handData.R_w2o(2,2) ); 

    fclose(fp); 

}



double FrameExporter::readMotionCaptureData(const char * filename, HandData & handData)
{

    printf("---\n"); 
    printf("HandData read from %s: \n", filename); 

    ifstream infile(filename); 

    if (!infile)
    {
        cerr << "** Cannot find hand data at " << filename << ". Return. " << endl; 
        return -1; 
    }

    string line; 

    double time; 

    {
        getline(infile, line); 
        cout << line << endl;
        istringstream iss(line); 
        iss >> time; 
    }


    {
        getline(infile, line); 
        istringstream iss(line); 
        double buff[3]; 
        iss >> buff[0] >> buff[1] >> buff[2]; 
        handData.tipPos[0] = buff[0]; 
        handData.tipPos[1] = buff[1]; 
        handData.tipPos[2] = buff[2]; 
    }

    {
        getline(infile, line); 
        istringstream iss(line); 
        double buff[3]; 
        iss >> buff[0] >> buff[1] >> buff[2]; 
        handData.tipVel[0] = buff[0]; 
        handData.tipVel[1] = buff[1]; 
        handData.tipVel[2] = buff[2]; 
    }


    {
        getline(infile, line); 
        istringstream iss(line); 
        double buff[3]; 
        iss >> buff[0] >> buff[1] >> buff[2]; 
        handData.handDir[0] = buff[0]; 
        handData.handDir[1] = buff[1]; 
        handData.handDir[2] = buff[2]; 
    }

    {
        getline(infile, line); 
        istringstream iss(line); 
        double buff[3]; 
        iss >> buff[0] >> buff[1] >> buff[2]; 
        handData.palmNor[0] = buff[0]; 
        handData.palmNor[1] = buff[1]; 
        handData.palmNor[2] = buff[2]; 
    }

    Eigen::Vector3d tmp = handData.handDir.cross(handData.palmNor); 
    tmp.normalize();
    handData.R_w2o.col(0) = handData.palmNor; 
    handData.R_w2o.col(1) = tmp; 
    handData.R_w2o.col(2) = handData.handDir; 

    handData.R_w2o.transposeInPlace(); 

    //printf("tipPos = %.9f %.9f %.9f\n" , handData.tipPos[0]
    //                                   , handData.tipPos[1]
    //                                   , handData.tipPos[2]); 
    //printf("tipVel = %.9f %.9f %.9f\n" , handData.tipVel[0]
    //                                   , handData.tipVel[1]
    //                                   , handData.tipVel[2]); 
    //printf("handDir = %.9f %.9f %.9f\n", handData.handDir[0]
    //                                   , handData.handDir[1]
    //                                   , handData.handDir[2]); 
    //printf("palmNor = %.9f %.9f %.9f\n", handData.palmNor[0]
    //                                   , handData.palmNor[1]
    //                                   , handData.palmNor[2]); 

    return time; 

}
