#include "ui_window.h"

#include <QtGui>

#include <math.h>

#include "parameters.h"

using namespace std;

Particles::Particles()
{
    init(); 
}

int Particles::ageMax = 10;

void Particles::init()
{
    _pos.setZero(); 
    _age = 0.0; 
}

void Particles::draw()
{
    glColor3f(_age/(float)ageMax, _age/(float)ageMax, 1.0); 
    glVertex3f((float)_pos(0),(float)_pos(1),(float)_pos(2)); 
}

void Particles::animate()
{
    draw(); 
}


AudioGUI::AudioGUI(Engine * eng, VisualGUI * vgui, QWidget *parent) : QWidget(parent), _useLeapMotion(false), _eng(eng), _vgui(vgui)
{
    /* gain two-way communication */
    vgui->set_agui(this); 

    /* to be exception-safe. */
    _startStreamButton = new AudioStreamButton("Start stream", this); 
    _stopStreamButton  = new AudioStreamButton("Stop stream", this); 
    _sensitivitySlider = new QSlider(Qt::Vertical, this); 
    _sharpnessSlider = new QSlider(Qt::Vertical, this); 
    _frequencyShiftCheck = new QCheckBox("Frequency shift", this); 
    _useLeapMotionCheck = new QCheckBox("Use Leap Motion", this); 

    _sensitivitySliderMsg = new QLabel("5");
    _sharpnessSliderMsg = new QLabel("2");
    _sensitivitySliderLabel = new QLabel("Sensitivity"); 
    _sharpnessSliderLabel = new QLabel("Amp Mag");

    connect(_startStreamButton, SIGNAL(clicked()), 
            this, SLOT(startStreamClicked())); 
    connect(_stopStreamButton, SIGNAL(clicked()), 
            this, SLOT(stopStreamClicked())); 
    connect(_sensitivitySlider, SIGNAL(valueChanged(int)),
            this, SLOT(updateSensitivity()));
    connect(_sharpnessSlider, SIGNAL(valueChanged(int)), 
            this, SLOT(updateSharpness()));
    connect(_frequencyShiftCheck, SIGNAL(stateChanged(int)), 
            this, SLOT(toggleFrequencyShift())); 
    connect(_useLeapMotionCheck, SIGNAL(stateChanged(int)), 
            this, SLOT(toggleUseLeapMotion())); 

    _sensitivitySlider->setRange(30, 100); 
    _sensitivitySlider->setValue(50); 
    _sensitivitySlider->setPageStep(1);

    _sharpnessSlider->setRange(10, 30); 
    _sharpnessSlider->setValue(10); 
    _sharpnessSlider->setPageStep(1);


    /* set button layout */

    QGridLayout *mainLayout = new QGridLayout; 

    mainLayout->addWidget(_vgui, 0, 0);
    mainLayout->addWidget(_sensitivitySlider, 0, 1); 
    mainLayout->addWidget(_sensitivitySliderMsg, 1, 1); 
    mainLayout->addWidget(_sensitivitySliderLabel, 2, 1); 
    mainLayout->addWidget(_sharpnessSlider, 0, 2); 
    mainLayout->addWidget(_sharpnessSliderMsg, 1, 2); 
    mainLayout->addWidget(_sharpnessSliderLabel, 2, 2); 

    mainLayout->addWidget(_frequencyShiftCheck, 1, 0); 
    mainLayout->addWidget(_useLeapMotionCheck, 2, 0);
    mainLayout->addWidget(_startStreamButton, 3, 0); 
    mainLayout->addWidget(_stopStreamButton, 4, 0); 


    //mainLayout->setAlignment(Qt::AlignCenter);
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

//void AudioGUI::updateMaxspeed()
//{
//    //cout << "Max speed = " << getMaxspeed() << endl;
//}

void AudioGUI::toggleFrequencyShift()
{
    _eng->toggleFrequencyShift(); 
}

void AudioGUI::toggleUseLeapMotion()
{
    _useLeapMotion = ! _useLeapMotion; 
    cout << "Use Leap Motion for velocity tracking = " << _useLeapMotion << endl; 

    if (_useLeapMotion) 
        _leapmotion = new LeapMotion(); 
    else 
    {
        if (_leapmotion != NULL)
            delete _leapmotion; 
    }

}


AudioStreamButton::AudioStreamButton(const QString &text, QWidget *parent) : QPushButton(text, parent)
{
    //do nothing
}


void VisualGUI::draw()
{

    if (NULL != _agui->_leapmotion && _agui->_leapmotion->gotFirstFrame())
    {
        Eigen::MatrixXd * tmp = new Eigen::MatrixXd(); 
        tmp->setZero(3,1); 
        _agui->_leapmotion->getIndexFingerPos(tmp); 

        if ((*tmp) != _plist[_lastPart].getPos())
        {
            for (int ii=0; ii<Particles::ageMax; ii++)
                _plist[ii].growOld(); 
            
            _plist[_lastPart].init();
            _plist[_lastPart].setPos((Eigen::Vector3d) (*tmp));
            _lastPart ++; 
            _lastPart = _lastPart == Particles::ageMax ? 0 : _lastPart;
        }

        glBegin(GL_POINTS); 
        for (int ii=0; ii<Particles::ageMax; ii++)
        {
            _plist[ii].draw(); 
        }
        glEnd(); 

        //cout << " drawing " << endl;
        //Eigen::MatrixXd * tmp = new Eigen::MatrixXd(); 
        //tmp->setZero(3,1); 
        //_agui->_leapmotion->getIndexFingerPos(tmp); 

        //glBegin(GL_POINTS);
        //glColor3f(1.0f,1.0f,1.0f); 
        //glVertex3f((float)(*tmp)(0),(float)(*tmp)(1),(float)(*tmp)(2)); 
        //glEnd(); 
    }

}

void VisualGUI::init()
{
    // Restore previous viewer state.
    restoreStateFromFile();
    glPointSize(6.0);
    setAnimationPeriod(0.0);

    _nbPart = Particles::ageMax; 

    _plist = new Particles[_nbPart]; 
    _lastPart = 0; 

    for (int ii=0; ii<Particles::ageMax; ii++)
    {
        Eigen::MatrixXd * tmp = new Eigen::MatrixXd(3,1); 
        tmp->setZero(); 
        _plist[ii].growOld();
    }


    // set mouse tracking
    setMouseTracking(true); 
    setGridIsDrawn(); 

    startAnimation();

    // Set 'Control+F' as the FPS toggle state key.
    setShortcut(DISPLAY_FPS, Qt::CTRL+Qt::Key_F);

}

void VisualGUI::animate()
{
    //draw(); 
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

void VisualGUI::computeMouseSpeed(QMouseEvent* const e)
{

    //QPoint mousePos = this->mapFromGlobal(QCursor::pos());
    QPoint mousePos = e->pos();
    //cout << "p = " << p.x() << ", " << p.y() << endl;
    //cout << "mousePos = " << mousePos.x() << ", " << mousePos.y() << endl;

    const QPoint delta = (mousePos - _prevPos);
    _prevPos = mousePos; 
    const float dist = sqrt(static_cast<float>(delta.x()*delta.x() + delta.y()*delta.y()));
    _delay = _lastMoveTime.restart();
    //cout << "refresh rate = " << 1.0/_delay*1000 << endl; 
    _prevMouseSpeed = _mouseSpeed; 

    if (_delay == 0) // Less than a millisecond: assume delay = 1ms
        _mouseSpeed = dist;
    else
        _mouseSpeed = dist/_delay;

    sndState::prevMouseSpeed = _prevMouseSpeed; 
    sndState::currMouseSpeed = _mouseSpeed;

    //cout << "speed_mouse = " << _mouseSpeed << endl;

    /* set the mouse speed to zero if inside bufferzone */
    if (((width()-mousePos.x())<PARAMETERS::BUFFERZONE) || ((height()-mousePos.y())<PARAMETERS::BUFFERZONE) || mousePos.x() < PARAMETERS::BUFFERZONE || mousePos.y() < PARAMETERS::BUFFERZONE)
        _mouseSpeed = 0.0;
}

void VisualGUI:: updateCamera()
{
    myCamera._camera = this->camera(); 
    qglviewer::Vec tmpPos = myCamera._camera->position(); 
    myCamera._position[0] = tmpPos.x;
    myCamera._position[1] = tmpPos.y; 
    myCamera._position[2] = tmpPos.z; 
}

void VisualGUI::mouseMoveEvent(QMouseEvent* const e)
{

    if (e->modifiers() == Qt::AltModifier)
        computeMouseSpeed(e); 
    else 
        _mouseSpeed = 0.0;

}


void Engine::computeMouseSpeed()
{
    //_vgui->computeMouseSpeed();
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
