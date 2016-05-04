TARGET = aerosound_mocap

### Debug flags ###
# CONFIG += qt opengl debug c++11 
# QMAKE_CXXFLAGS += -std=c++11 -g -Wno-deprecated-register
###       
 
CONFIG += qt opengl release c++11 
QMAKE_CXXFLAGS += -std=c++11 -Wno-deprecated-register


QT += opengl xml widgets

HEADERS += ./include/readsound.h \
           ./include/sourcefunction.h \
           ./include/streamsound.h \
           ./include/ui_window.h \
           ./include/LeapMotion.h \
           ./include/ObjectLoader.h \
           ./include/auxFunc.h \
           ./include/FrameExporter.h \
           ./parameters.h \


SOURCES += ./main.cpp \ 
           ./src/sourcefunction.cpp \
           ./src/streamsound.cpp \
           ./src/ui_window.cpp \
           ./src/LeapMotion.cpp \ 
           ./src/ObjectLoader.cpp \ 
           ./src/FrameExporter.cpp \



INCLUDEPATH += ./ \
		       ./include \
		       ../turbsound_postfluid/tools \
               /Users/jui-hsienwang/portaudio/portaudio/include \
		       /Users/jui-hsienwang/portaudio/portaudio/src/common \
		       /usr/local/Cellar/eigen/3.2.2/include/eigen3 \
               /Users/jui-hsienwang/libQGLViewer/libQGLViewer-2.5.3 \
               /Users/jui-hsienwang/LeapMotion/LeapDeveloperKit_2.2.5+26752_mac/LeapSDK/include


LIBS += /Users/jui-hsienwang/portaudio/portaudio/lib/.libs/libportaudio.a \
	    -lsndfile

LIBS += -F/Users/jui-hsienwang/Library/Frameworks -framework QGLViewer

LIBS += /Users/jui-hsienwang/LeapMotion/LeapDeveloperKit_2.2.5+26752_mac/LeapSDK/lib/libLeap.dylib


LIBS += -framework CoreAudio \
        -framework AudioUnit \
        -framework AudioToolbox \
        -framework Carbon

