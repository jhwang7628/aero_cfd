#include "Leap.h" 
#include "LeapMotion.h"
#include <iostream> 
#include <unistd.h>

#include "streamsound.h"

using namespace std; 
using namespace Leap; 

void LeapListener::onInit(const Controller& controller) {
    std::cout << "Initialized" << std::endl;
}

void LeapListener::onConnect(const Controller& controller) {
    std::cout << "Connected" << std::endl;
    //controller.enableGesture(Gesture::TYPE_CIRCLE);
    //controller.enableGesture(Gesture::TYPE_KEY_TAP);
    //controller.enableGesture(Gesture::TYPE_SCREEN_TAP);
    //controller.enableGesture(Gesture::TYPE_SWIPE);
}

void LeapListener::onDisconnect(const Controller& controller) {
    // Note: not dispatched when running in a debugger.
    std::cout << "Disconnected" << std::endl;
}

void LeapListener::onExit(const Controller& controller) {
    std::cout << "Exited" << std::endl;
}

/* callback function when new frame is available */
void LeapListener::onFrame(const Controller& controller) {
    const Frame frame = controller.frame();

    if (frame.id() != -1)
        _lm->setGotFirstFrame(true); 

    HandList hands = frame.hands();
    for (HandList::const_iterator hl = hands.begin(); hl != hands.end(); ++hl) {
        // Get the first hand
        const Hand hand = *hl;

        // Get fingers
        const FingerList fingers = hand.fingers();
        for (FingerList::const_iterator fl = fingers.begin(); fl != fingers.end(); ++fl) 
        {
            const Finger finger = *fl;
            /* Only tracking the index finger */
            if (finger.type() == 1) 
            {
                cout << "index finger : pos, vel = " << finger.tipPosition() << ", " << finger.tipVelocity() << endl;
                _lm->setIndexFingerState(finger.tipPosition(), finger.tipVelocity()); 
                Eigen::MatrixXd *vel = new Eigen::MatrixXd(); 
                vel->setZero(3,1); 
                _lm->getIndexFingerVel(vel); 

                double speed = vel->norm();

                sndState::prevMouseSpeed = sndState::currMouseSpeed;
                sndState::currMouseSpeed = speed*3.0; 

                //cout << "speed = " << speed << endl; 


            }

        }
    }

    if (!frame.hands().isEmpty()) 
        std::cout << std::endl;
}

void LeapListener::onFocusGained(const Controller& controller) {
    std::cout << "Focus Gained" << std::endl;
}

void LeapListener::onFocusLost(const Controller& controller) {
    std::cout << "Focus Lost" << std::endl;
}

void LeapListener::onDeviceChange(const Controller& controller) {
    std::cout << "Device Changed" << std::endl;
    const DeviceList devices = controller.devices();

    for (int i = 0; i < devices.count(); ++i) {
        std::cout << "id: " << devices[i].toString() << std::endl;
        std::cout << "  isStreaming: " << (devices[i].isStreaming() ? "true" : "false") << std::endl;
    }
}

void LeapListener::onServiceConnect(const Controller& controller) {
    std::cout << "Service Connected" << std::endl;
}

void LeapListener::onServiceDisconnect(const Controller& controller) {
    std::cout << "Service Disconnected" << std::endl;
}

///////////////////////////////////////////

LeapMotion::LeapMotion() : _gotFirstFrame(false)
{
    listener = new LeapListener(this); 
    controller = new Controller();  

    _indexFingerPos = new Leap::Vector(); 
    _indexFingerVel = new Leap::Vector(); 

    if (_indexFingerPos == NULL)
        cout << "_indexFingerPos = null" << endl;

    controller->addListener(*listener); 

    controller->setPolicy(Controller::POLICY_BACKGROUND_FRAMES);

    cout << "Leap Motion controller initialized for background applications. " << endl;

    // const std::string fingerNames[] = {"Thumb", "Index", "Middle", "Ring", "Pinky"};
    // const std::string boneNames[] = {"Metacarpal", "Proximal", "Middle", "Distal"};
    // const std::string stateNames[] = {"STATE_INVALID", "STATE_START", "STATE_UPDATE", "STATE_END"};

}

LeapMotion::~LeapMotion()
{
    controller->removeListener(*listener);
    //if (listener != NULL)
    //    delete listener; 
        cout << "before delete: _indexFingerPos = null" << endl;
    delete controller; 
}

void LeapMotion::setIndexFingerState(Leap::Vector pos, Leap::Vector vel) 
{
    _indexFingerPos = new Leap::Vector(pos); 
    _indexFingerVel = new Leap::Vector(vel); 
}

void LeapMotion::getIndexFingerPos(Eigen::MatrixXd * pos)
{
    (*pos)(0,0) = _indexFingerPos->x/1000.0; 
    (*pos)(1,0) = _indexFingerPos->y/1000.0; 
    (*pos)(2,0) = _indexFingerPos->z/1000.0; 
}
    
void LeapMotion::getIndexFingerVel(Eigen::MatrixXd * vel)
{
    (*vel)(0,0) = _indexFingerVel->x/1000.0; 
    (*vel)(1,0) = _indexFingerVel->y/1000.0; 
    (*vel)(2,0) = _indexFingerVel->z/1000.0; 
}

void LeapMotion::setGotFirstFrame(const bool g)
{
    _gotFirstFrame = g; 
}

bool LeapMotion::gotFirstFrame()
{
    return _gotFirstFrame; 
}


#if 0 // testing
int main()
{

    LeapMotion lm; 

    std::cout << "Press Enter to quit..." << std::endl;
    cin.get(); 

    return 0;

}

#endif 
