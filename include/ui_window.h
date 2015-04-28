#ifndef UI_WINDOW_H
#define UI_WINDOW_H

#include <QWidget>
#include <QPushButton>
#include <qapplication.h>
#include <QGLViewer/qglviewer.h>

#include "streamsound.h"


class Engine;
class VisualGUI : public QGLViewer
{

    private :
        Engine * _eng; 
        bool _wireframe; 
        bool _flatShading;
            
    public:
        VisualGUI(Engine * eng) : _eng(eng) {}

    protected :
        virtual void draw();
        virtual void init();
        virtual void keyPressEvent(QKeyEvent *e);
        virtual void mousePressEvent(QMouseEvent* e);

        virtual QString helpString() const;

};


class AudioStreamButton : public QPushButton
{
    Q_OBJECT

    public : 
        AudioStreamButton(const QString &text, QWidget *parent=0); 

};

class AudioGUI : public QWidget
{
    Q_OBJECT

    private : 
        Engine * _eng; 
        VisualGUI * _vgui; 
        AudioStreamButton * _startStreamButton; 
        AudioStreamButton * _stopStreamButton; 

    public : 
        AudioGUI(Engine * eng, VisualGUI * vgui, QWidget *parent=0); 
        ~AudioGUI(){}

    private slots : 
        void startStreamClicked(); 
        void stopStreamClicked(); 

    //void setQA(QApplication * qa);
    //void setUI(); 

};

#endif
