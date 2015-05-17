#ifndef UI_WINDOW_H
#define UI_WINDOW_H

#include <QtGui>
#include <QTime>
#include <qapplication.h>
#include <QGLViewer/qglviewer.h>

#include "LeapMotion.h"

#include "streamsound.h"


class Engine;
class AudioGUI;

class Particles 
{
    private:
        Eigen::Vector3d _pos; 
        int _age; 

    public: 
        static int ageMax; 

        Particles();

        void init(); 
        void draw(); 
        void animate(); 

        Eigen::Vector3d getPos()
        {
            return _pos; 
        }

        void setPos(Eigen::Vector3d pos)
        {
            _pos = pos; 
        }

        void growOld()
        {
            _age++; 
        }


};

class VisualGUI : public QGLViewer
{

    private :
        Engine * _eng; 
        AudioGUI * _agui; 

        struct myCamera
        {
            qglviewer::Camera * _camera; 
            Eigen::Vector3d _position; 
        } myCamera; 



        int _nbPart;
        int _lastPart;  // a pointer pointing to the last particle
        Particles * _plist; 

        bool _wireframe; 
        bool _flatShading;

        QTime _lastMoveTime; 
        int _delay; 
        double _prevMouseSpeed; 
        double _mouseSpeed;
	    QPoint _prevPos, _pressPos;

    protected :
        virtual void draw();
        virtual void animate(); 
        virtual void init();
        virtual void keyPressEvent(QKeyEvent *e);
        virtual void mousePressEvent(QMouseEvent* e);
        virtual void mouseMoveEvent(QMouseEvent* const e);

    public:
        VisualGUI(Engine * eng) : _eng(eng) {}
        void set_agui(AudioGUI * agui)
        {
            _agui = agui; 
        }

        void computeMouseSpeed(QMouseEvent* const e); 

        void updateCamera(); 


};


class AudioStreamButton : public QPushButton
{
    Q_OBJECT

    public : 
        AudioStreamButton(const QString &text, QWidget *parent=0); 
        ~AudioStreamButton(){}
};

class AudioGUI : public QWidget
{
    Q_OBJECT

    private : 

        bool _useLeapMotion; 

        Engine * _eng; 
        VisualGUI * _vgui; 

        AudioStreamButton * _startStreamButton; 
        AudioStreamButton * _stopStreamButton; 
        QSlider * _sensitivitySlider; 
        QSlider * _sharpnessSlider; 
        QLabel * _sensitivitySliderMsg; 
        QLabel * _sharpnessSliderMsg; 
        QLabel * _sensitivitySliderLabel; 
        QLabel * _sharpnessSliderLabel;
        QCheckBox * _frequencyShiftCheck; 
        QCheckBox * _useLeapMotionCheck; 

    public : 
        LeapMotion * _leapmotion; 
        AudioGUI(Engine * eng, VisualGUI * vgui, QWidget *parent=0); 
        ~AudioGUI(){}

        double getSensitivity()
        {
            return (double)_sensitivitySlider->value()/10.0;
        }

        double getSharpness()
        {
            return (double)_sharpnessSlider->value()/10.0; 
        }

        private slots : 
            void startStreamClicked(); 
            void stopStreamClicked(); 
            void toggleFrequencyShift(); 
            void toggleUseLeapMotion();
            void updateSensitivity()
            {
                _sensitivitySliderMsg->setText(QString("%1").arg(getSensitivity()));
            }
            void updateSharpness()
            {
                _sharpnessSliderMsg->setText(QString("%1").arg(getSharpness()));
            }

        //void setQA(QApplication * qa);
        //void setUI(); 

};


#endif
