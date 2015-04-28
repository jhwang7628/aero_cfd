#ifndef UI_WINDOW_H
#define UI_WINDOW_H

#include <qapplication.h>
#include <QtGui>
#include <QObject>
#include <QPushButton>

#include <QGLViewer/qglviewer.h>

class Viewer : public QGLViewer
{
    public:
        Viewer() : wireframe_(false), flatShading_(false) {};

    protected :
        virtual void draw();
        virtual void init();
        virtual void keyPressEvent(QKeyEvent *e);
        virtual void mousePressEvent(QMouseEvent* e);

        virtual QString helpString() const;

    private :
        bool wireframe_, flatShading_;
};

class streamControlPushButton : public QPushButton
{
    Q_OBJECT

    public : 
        streamControlPushButton(const QString & c) : QPushButton(c) {}

        public slots: 
        void QOpenStream(){}

}; 


class AudioGUI : public QWidget
{


    QApplication * _application; 

    QWidget window; 
    streamControlPushButton *startStreamButton; 


    public : 

    GUI(){}
    ~GUI(){}

    void setQA(QApplication * qa);
    void setUI(); 

};


#endif
