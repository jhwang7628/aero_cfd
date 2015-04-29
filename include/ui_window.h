#ifndef UI_WINDOW_H
#define UI_WINDOW_H

#include <QtGui>
#include <QTime>
#include <qapplication.h>
#include <QGLViewer/qglviewer.h>

#include "streamsound.h"


class Engine;
class AudioGUI;

class VisualGUI : public QGLViewer
{

    private :
        Engine * _eng; 
        AudioGUI * _agui; 

        bool _wireframe; 
        bool _flatShading;

        QTime _lastMoveTime; 
        int _delay; 
        double _mouseSpeed;
	    QPoint _prevPos, _pressPos;

    protected :
        virtual void draw();
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

        void computeMouseSpeed(const QMouseEvent * const e); 


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
        Engine * _eng; 
        VisualGUI * _vgui; 
        AudioStreamButton * _startStreamButton; 
        AudioStreamButton * _stopStreamButton; 
        QSlider * _maxspeedSlider; 

    public : 
        AudioGUI(Engine * eng, VisualGUI * vgui, QWidget *parent=0); 
        ~AudioGUI(){}

        double getMaxspeed()
        {
            return _maxspeedSlider->value();
        }

        private slots : 
            void startStreamClicked(); 
            void stopStreamClicked(); 
            void updateMaxspeed(); 

        //void setQA(QApplication * qa);
        //void setUI(); 

};

#endif
