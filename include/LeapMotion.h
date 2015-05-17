#ifndef LEAPMOTION_H
#define LEAPMOTION_H

#include <iostream> 
#include <unistd.h>
#include <Eigen/Dense>
#include "Leap.h"

using namespace std; 
using namespace Leap; 


class LeapMotion; 
class LeapListener : public Listener
{
    private: 
        LeapMotion * _lm; 
    public:

        LeapListener(LeapMotion * lm) : _lm(lm) {}
        ~LeapListener() {}

        virtual void onInit(const Controller &); 
        virtual void onConnect(const Controller &); 
        virtual void onDisconnect(const Controller &); 
        virtual void onExit(const Controller&);
        virtual void onFrame(const Controller&);
        virtual void onFocusGained(const Controller&);
        virtual void onFocusLost(const Controller&);
        virtual void onDeviceChange(const Controller&);
        virtual void onServiceConnect(const Controller&);
        virtual void onServiceDisconnect(const Controller&);
};

class LeapMotion
{
    private:

        LeapListener * listener; 
        Controller * controller; 

        /* in millimeter */
        Leap::Vector * _indexFingerPos; 
        Leap::Vector * _indexFingerVel; 

        bool _gotFirstFrame;

    public: 

        LeapMotion();
        ~LeapMotion();

        void setIndexFingerState(Leap::Vector pos, Leap::Vector vel);
        void getIndexFingerPos(Eigen::MatrixXd * pos);
        void getIndexFingerVel(Eigen::MatrixXd * vel);
        void setGotFirstFrame(const bool g); 
        bool gotFirstFrame();

}; 


#endif
