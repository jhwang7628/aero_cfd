#ifndef OBJECTLOADER_H
#define OBJECTLOADER_H

#include "streamsound.h"



class ObjectLoader
{

    public: 

        static int sampleInterval; 

        static void loadCylinder(Engine & eng); 
        static void loadCylinderRepeat(Engine & eng); 
        static void loadSquare(Engine & eng); 
        static void loadSword(Engine & eng);
}; 


#endif
