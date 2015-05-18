#include "FrameExporter.h"
#include "LeapMotion.h"
#include "auxFunc.h"
#include <string>


using namespace std; 

int FrameExporter::frame = 0;

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

    FrameExporter::frame ++;

}



double FrameExporter::readMotionCaptureData(HandData & handData)
{
}
