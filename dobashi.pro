TARGET = dobashi 
CONFIG += qt opengl release c++11
QMAKE_CXXFLAGS += -std=c++11 -Wno-deprecated-register
QT += opengl xml widgets

HEADERS += ./include/readsound.h \
           ./include/sourcefunction.h \
           ./include/streamsound.h \
           ./include/ui_window.h \
           ./parameters.h


SOURCES += ./main.cpp \ 
           ./src/sourcefunction.cpp \
           ./src/streamsound.cpp \
           ./src/ui_window.cpp


INCLUDEPATH += ./ \
		       ./include \
		       ../turbsound_postfluid/tools \
               /Users/jui-hsienwang/portaudio/portaudio/include \
		       /Users/jui-hsienwang/portaudio/portaudio/src/common \
		       /usr/local/Cellar/eigen/3.2.2/include/eigen3 \
               /Users/jui-hsienwang/libQGLViewer/libQGLViewer-2.5.3


LIBS += /Users/jui-hsienwang/portaudio/portaudio/lib/.libs/libportaudio.a \
	    -lsndfile

LIBS += -F/Users/jui-hsienwang/Library/Frameworks -framework QGLViewer

LIBS += -framework CoreAudio \
        -framework AudioUnit \
        -framework AudioToolbox \
        -framework Carbon


