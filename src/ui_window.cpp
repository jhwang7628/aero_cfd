#include "ui_window.h"

#include <QtGui>

#include <math.h>

using namespace std;



AudioGUI::AudioGUI(Engine * eng, VisualGUI * vgui, QWidget *parent) : QWidget(parent), _eng(eng), _vgui(vgui)
{
    /* gain two-way communication */
    vgui->set_agui(this); 

    /* to be exception-safe. */
    _startStreamButton = new AudioStreamButton("Start stream", this); 
    _stopStreamButton  = new AudioStreamButton("Stop stream", this); 
    _maxspeedSlider = new QSlider(Qt::Vertical, this); 

    connect(_startStreamButton, SIGNAL(clicked()), 
            this, SLOT(startStreamClicked())); 
    connect(_stopStreamButton, SIGNAL(clicked()), 
            this, SLOT(stopStreamClicked())); 
    connect(_maxspeedSlider, SIGNAL(valueChanged(int)),
            this, SLOT(updateMaxspeed()));

    _maxspeedSlider->setRange(0,150); 
    _maxspeedSlider->setValue(25); 
    _maxspeedSlider->setPageStep(1);

    /* set button layout */

    QGridLayout *mainLayout = new QGridLayout; 

    mainLayout->addWidget(_vgui, 0, 0);
    mainLayout->addWidget(_maxspeedSlider, 0, 1); 
    mainLayout->addWidget(_startStreamButton, 1, 0); 
    mainLayout->addWidget(_stopStreamButton, 2, 0); 

    setLayout(mainLayout); 
    setWindowTitle("Audio Control Panel");
    resize(800, 600); 

    show(); 
}


void AudioGUI::startStreamClicked() 
{
    cout << "Starting audio stream..." << endl; 
    _eng->StartStream(); 
}
void AudioGUI::stopStreamClicked() 
{

    cout << "Stoping audio stream..." << endl; 
    _eng->StopStream();
}

void AudioGUI::updateMaxspeed()
{
    cout << "Max speed = " << getMaxspeed() << endl;
}


AudioStreamButton::AudioStreamButton(const QString &text, QWidget *parent) : QPushButton(text, parent)
{
    //do nothing
}





// Draws a spiral
void VisualGUI::draw()
{
#if 0


    /* testing */
    const float nbSteps = 80.0;

    glBegin(GL_QUAD_STRIP);
    for (float i=0; i<nbSteps; ++i)
    {
        float ratio = i/nbSteps;
        float angle = 21.0*ratio;
        float c = cos(angle);
        float s = sin(angle);
        float r1 = 1.0 - 0.8*ratio;
        float r2 = 0.8 - 0.8*ratio;
        float alt = ratio - 0.5;
        const float nor = .5;
        const float up = sqrt(1.0-nor*nor);
        glColor3f(fabs(c), 0.2f, fabs(s));
        glNormal3f(nor*c, up, nor*s);
        glVertex3f(r1*c, alt, r1*s);
        glVertex3f(r2*c, alt+0.05, r2*s);
    }
    glEnd();
#endif
}

void VisualGUI::init()
{
    // Restore previous viewer state.
    restoreStateFromFile();

    // set mouse tracking
    setMouseTracking(true); 

    // Set 'Control+F' as the FPS toggle state key.
    setShortcut(DISPLAY_FPS, Qt::CTRL+Qt::Key_F);

    // Disable draw grid toggle shortcut (default was 'G')
    //setShortcut(DRAW_GRID, 0);




    /////////////////////////////////////////////////////
    //         Mouse bindings customization            //
    //     Changes standard action mouse bindings      //
    /////////////////////////////////////////////////////

    // Left and right buttons together make a camera zoom : emulates a mouse third button if needed.
    //setMouseBinding(Qt::Key_Z, Qt::NoModifier, Qt::LeftButton, CAMERA, ZOOM);

    //// Disable previous TRANSLATE mouse binding (and remove it from help mouse tab).
    //setMouseBinding(Qt::NoModifier, Qt::RightButton, NO_CLICK_ACTION);

    //setMouseBinding(Qt::ControlModifier | Qt::ShiftModifier, Qt::RightButton, SELECT);
    //setWheelBinding(Qt::AltModifier, CAMERA, MOVE_FORWARD);
    //setMouseBinding(Qt::AltModifier, Qt::LeftButton, CAMERA, TRANSLATE);

    //// Add custom mouse bindings description (see mousePressEvent())
    //setMouseBindingDescription(Qt::NoModifier, Qt::RightButton, "Opens a camera path context menu");

}


void VisualGUI::keyPressEvent(QKeyEvent *e)
{
    // Get event modifiers key
    const Qt::KeyboardModifiers modifiers = e->modifiers();

    // A simple switch on e->key() is not sufficient if we want to take state key into account.
    // With a switch, it would have been impossible to separate 'F' from 'CTRL+F'.
    // That's why we use imbricated if...else and a "handled" boolean.
    bool handled = false;
    if ((e->key()==Qt::Key_W) && (modifiers==Qt::NoButton))
    {
        _wireframe = !_wireframe;
        if (_wireframe)
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        else
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        handled = true;
        updateGL();
    }
    else
        if ((e->key()==Qt::Key_F) && (modifiers==Qt::NoButton))
        {
            _flatShading = !_flatShading;
            if (_flatShading)
                glShadeModel(GL_FLAT);
            else
                glShadeModel(GL_SMOOTH);
            handled = true;
            updateGL();
        }
    // ... and so on with other else/if blocks.

    if (!handled)
        QGLViewer::keyPressEvent(e);
}



#if 0
QString VisualGUI::helpString() const
{
    QString text("<h2>K e y b o a r d A n d M o u s e</h2>");
    text += "This example illustrates the mouse and key bindings customization.<br><br>";
    text += "Use <code>setShortcut()</code> to change standard action key bindings (display of axis, grid or fps, exit shortcut...).<br><br>";
    text += "Use <code>setMouseBinding()</code> and <code>setWheelBinding()</code> to change standard action mouse bindings ";
    text += "(camera rotation, translation, object selection...).<br><br>";
    text += "If you want to define <b>new</b> key or mouse actions, overload <code>keyPressEvent()</code> and/or ";
    text += "<code>mouse(Press|Move|Release)Event()</code> to define and bind your own new actions. ";
    text += "Use <code>setKeyDescription()</code> and <code>setMouseBindingDescription()</code> to add a description of your bindings in the help window.<br><br>";
    text += "In this example, we defined the <b>F</b> and <b>W</b> keys and the right mouse button opens a popup menu. ";
    text += "See the keyboard and mouse tabs in this help window for the complete bindings description.<br><br>";
    text += "By the way, exit shortcut has been binded to <b>Ctrl+Q</b>.";
    return text;
}
#endif 

void VisualGUI::computeMouseSpeed(const QMouseEvent * const e)
{
    const QPoint delta = (e->pos() - _prevPos);
    _prevPos = e->pos(); 
    const float dist = sqrt(static_cast<float>(delta.x()*delta.x() + delta.y()*delta.y()));
    _delay = _lastMoveTime.restart();
    if (_delay == 0) // Less than a millisecond: assume delay = 1ms
        _mouseSpeed = dist;
    else
        _mouseSpeed = dist/_delay;
}

void VisualGUI::mouseMoveEvent(QMouseEvent* const e)
{

    if (e->modifiers() == Qt::AltModifier)
        computeMouseSpeed(e); 
    else 
        _mouseSpeed = 0.0;

    _eng->setExtraScaling(_mouseSpeed/(_agui->getMaxspeed())); 
    //cout << "mouse speed = " << _mouseSpeed << endl;

}

void VisualGUI::mousePressEvent(QMouseEvent* e)
{
#if 0
    cout << "mouse pressed! " << endl;

    cout << hasMouseTracking() << endl;


    if ((e->button() == Qt::RightButton) && (e->modifiers() == Qt::NoButton))
    {
        cout << " hehe " << endl;
        QMenu menu( this );
        menu.addAction("Camera positions");
        menu.addSeparator();
        QMap<QAction*, int> menuMap;

        bool atLeastOne = false;
        // We only test the 20 first indexes. This is a limitation.
        for (unsigned short i=0; i<20; ++i)
            if (camera()->keyFrameInterpolator(i))
            {
                atLeastOne = true;
                QString text;
                if (camera()->keyFrameInterpolator(i)->numberOfKeyFrames() == 1)
                    text = "Position "+QString::number(i);
                else
                    text = "Path "+QString::number(i);

                menuMap[menu.addAction(text)] = i;
            }

        if (!atLeastOne)
        {
            menu.addAction("No position defined");
            menu.addAction("Use to Alt+Fx to define one");
        }

        QAction* action = menu.exec(e->globalPos());

        if (atLeastOne && action)
            camera()->playPath(menuMap[action]);
    }
    else
        QGLViewer::mousePressEvent(e);
#endif
}

#if 0
void AudioGUI::setQA(QApplication * qa) 
{
    _application = qa; 
}

void AudioGUI::setUI()
{

    startStreamButton = new streamControlPushButton("&Start audio stream.");

    //QObject::connect(startStreamButton, SIGNAL(clicked()), qApp, SLOT(QOpenStream()));

    //QVBoxLayout *layout = new QVBoxLayout(); 
    //layout->addWidget(startStreamButton); 

    window.resize(320, 240); 
    window.setWindowTitle("Hello QT!");
    window.show();
    //window.setLayout(layout);

}



//void streamControlPushButton::QOpenStream()
//{
//    _audio_engine->OpenStream(); 
//}

#endif
