#ifndef FRAMEEXPORTER_H
#define FRAMEEXPORTER_H


#include "LeapMotion.h"

/* 
 * Store/read motion capture data
 */
class FrameExporter
{
    public : 

        static int frame;

        static void readAllMotionCaptureData(const char * indir); 
        static void readAllMotionCaptureData(vector<HandData> & allhd, const char * indir);

        static void writeMotionCaptureData(const HandData & handData, const double time); 
        static double readMotionCaptureData(const char * filename, HandData & handData); 

}; 

#endif
