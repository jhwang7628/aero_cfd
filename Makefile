#############################################################################
# Makefile for building: dobashi.app/Contents/MacOS/dobashi
# Generated by qmake (2.01a) (Qt 4.8.6) on: Sun May 3 14:20:14 2015
# Project:  dobashi.pro
# Template: app
# Command: /usr/local/bin/qmake -spec /usr/local/Cellar/qt/4.8.6/mkspecs/macx-g++ -o Makefile dobashi.pro
#############################################################################

####### Compiler, tools and options

CC            = gcc
CXX           = g++
DEFINES       = -DQT_XML_LIB -DQT_OPENGL_LIB -DQT_GUI_LIB -DQT_CORE_LIB -DQT_SHARED
CFLAGS        = -pipe -g -arch x86_64 -Xarch_x86_64 -mmacosx-version-min=10.7 -Wall -W $(DEFINES)
CXXFLAGS      = -pipe -std=c++11 -Wno-deprecated-register -g -arch x86_64 -Xarch_x86_64 -mmacosx-version-min=10.7 -Wall -W $(DEFINES)
INCPATH       = -I/usr/local/Cellar/qt/4.8.6/mkspecs/macx-g++ -I. -I/usr/local/Cellar/qt/4.8.6/lib/QtCore.framework/Versions/4/Headers -I/usr/local/Cellar/qt/4.8.6/lib/QtCore.framework/Versions/4/Headers -I/usr/local/Cellar/qt/4.8.6/lib/QtGui.framework/Versions/4/Headers -I/usr/local/Cellar/qt/4.8.6/lib/QtGui.framework/Versions/4/Headers -I/usr/local/Cellar/qt/4.8.6/lib/QtOpenGL.framework/Versions/4/Headers -I/usr/local/Cellar/qt/4.8.6/lib/QtOpenGL.framework/Versions/4/Headers -I/usr/local/Cellar/qt/4.8.6/lib/QtXml.framework/Versions/4/Headers -I/usr/local/Cellar/qt/4.8.6/lib/QtXml.framework/Versions/4/Headers -I/usr/local/Cellar/qt/4.8.6/include -I. -Iinclude -I../turbsound_postfluid/tools -I../../portaudio/portaudio/include -I../../portaudio/portaudio/src/common -I/usr/local/Cellar/eigen/3.2.2/include/eigen3 -I../../libQGLViewer/libQGLViewer-2.5.3 -I/System/Library/Frameworks/OpenGL.framework/Versions/A/Headers -I/System/Library/Frameworks/AGL.framework/Headers -I. -F/usr/local/Cellar/qt/4.8.6/lib
LINK          = g++
LFLAGS        = -headerpad_max_install_names -arch x86_64 -Xarch_x86_64 -mmacosx-version-min=10.7
LIBS          = $(SUBLIBS) -F/usr/local/Cellar/qt/4.8.6/lib -L/usr/local/Cellar/qt/4.8.6/lib /Users/jui-hsienwang/portaudio/portaudio/lib/.libs/libportaudio.a -lsndfile -F/Users/jui-hsienwang/Library/Frameworks -framework QGLViewer -framework CoreAudio -framework AudioUnit -framework AudioToolbox -framework Carbon -framework OpenGL -framework AGL -framework QtXml -L/opt/X11/lib -L/usr/local/Cellar/qt/4.8.6/lib -F/usr/local/Cellar/qt/4.8.6/lib -framework QtCore -framework QtOpenGL -framework QtGui 
AR            = ar cq
RANLIB        = ranlib -s
QMAKE         = /usr/local/bin/qmake
TAR           = tar -cf
COMPRESS      = gzip -9f
COPY          = cp -f
SED           = sed
COPY_FILE     = cp -f
COPY_DIR      = cp -f -R
STRIP         = 
INSTALL_FILE  = $(COPY_FILE)
INSTALL_DIR   = $(COPY_DIR)
INSTALL_PROGRAM = $(COPY_FILE)
DEL_FILE      = rm -f
SYMLINK       = ln -f -s
DEL_DIR       = rmdir
MOVE          = mv -f
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p
export MACOSX_DEPLOYMENT_TARGET = 10.4

####### Output directory

OBJECTS_DIR   = ./

####### Files

SOURCES       = main.cpp \
		src/sourcefunction.cpp \
		src/streamsound.cpp \
		src/ui_window.cpp moc_ui_window.cpp
OBJECTS       = main.o \
		sourcefunction.o \
		streamsound.o \
		ui_window.o \
		moc_ui_window.o
DIST          = /usr/local/Cellar/qt/4.8.6/mkspecs/common/unix.conf \
		/usr/local/Cellar/qt/4.8.6/mkspecs/common/mac.conf \
		/usr/local/Cellar/qt/4.8.6/mkspecs/common/gcc-base.conf \
		/usr/local/Cellar/qt/4.8.6/mkspecs/common/gcc-base-macx.conf \
		/usr/local/Cellar/qt/4.8.6/mkspecs/common/g++-base.conf \
		/usr/local/Cellar/qt/4.8.6/mkspecs/common/g++-macx.conf \
		/usr/local/Cellar/qt/4.8.6/mkspecs/qconfig.pri \
		/usr/local/Cellar/qt/4.8.6/mkspecs/modules/qt_webkit_version.pri \
		/usr/local/Cellar/qt/4.8.6/mkspecs/features/qt_functions.prf \
		/usr/local/Cellar/qt/4.8.6/mkspecs/features/qt_config.prf \
		/usr/local/Cellar/qt/4.8.6/mkspecs/features/exclusive_builds.prf \
		/usr/local/Cellar/qt/4.8.6/mkspecs/features/default_pre.prf \
		/usr/local/Cellar/qt/4.8.6/mkspecs/features/mac/default_pre.prf \
		/usr/local/Cellar/qt/4.8.6/mkspecs/features/debug.prf \
		/usr/local/Cellar/qt/4.8.6/mkspecs/features/default_post.prf \
		/usr/local/Cellar/qt/4.8.6/mkspecs/features/mac/default_post.prf \
		/usr/local/Cellar/qt/4.8.6/mkspecs/features/mac/x86_64.prf \
		/usr/local/Cellar/qt/4.8.6/mkspecs/features/mac/objective_c.prf \
		/usr/local/Cellar/qt/4.8.6/mkspecs/features/unix/opengl.prf \
		/usr/local/Cellar/qt/4.8.6/mkspecs/features/qt.prf \
		/usr/local/Cellar/qt/4.8.6/mkspecs/features/unix/thread.prf \
		/usr/local/Cellar/qt/4.8.6/mkspecs/features/moc.prf \
		/usr/local/Cellar/qt/4.8.6/mkspecs/features/shared.prf \
		/usr/local/Cellar/qt/4.8.6/mkspecs/features/warn_on.prf \
		/usr/local/Cellar/qt/4.8.6/mkspecs/features/mac/rez.prf \
		/usr/local/Cellar/qt/4.8.6/mkspecs/features/mac/sdk.prf \
		/usr/local/Cellar/qt/4.8.6/mkspecs/features/resources.prf \
		/usr/local/Cellar/qt/4.8.6/mkspecs/features/uic.prf \
		/usr/local/Cellar/qt/4.8.6/mkspecs/features/yacc.prf \
		/usr/local/Cellar/qt/4.8.6/mkspecs/features/lex.prf \
		/usr/local/Cellar/qt/4.8.6/mkspecs/features/include_source_dir.prf \
		dobashi.pro
QMAKE_TARGET  = dobashi
DESTDIR       = 
TARGET        = dobashi.app/Contents/MacOS/dobashi

####### Custom Compiler Variables
QMAKE_COMP_QMAKE_OBJECTIVE_CFLAGS = -pipe \
		-g \
		-arch \
		x86_64 \
		-Xarch_x86_64 \
		-mmacosx-version-min=10.7 \
		-Wall \
		-W


first: all
####### Implicit rules

.SUFFIXES: .o .c .cpp .cc .cxx .C

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cc.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cxx.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.C.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.c.o:
	$(CC) -c $(CFLAGS) $(INCPATH) -o "$@" "$<"

####### Build rules

all: Makefile dobashi.app/Contents/PkgInfo dobashi.app/Contents/Resources/empty.lproj dobashi.app/Contents/Info.plist $(TARGET)

$(TARGET):  $(OBJECTS)  
	@$(CHK_DIR_EXISTS) dobashi.app/Contents/MacOS/ || $(MKDIR) dobashi.app/Contents/MacOS/ 
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(OBJCOMP) $(LIBS)

Makefile: dobashi.pro  /usr/local/Cellar/qt/4.8.6/mkspecs/macx-g++/qmake.conf /usr/local/Cellar/qt/4.8.6/mkspecs/common/unix.conf \
		/usr/local/Cellar/qt/4.8.6/mkspecs/common/mac.conf \
		/usr/local/Cellar/qt/4.8.6/mkspecs/common/gcc-base.conf \
		/usr/local/Cellar/qt/4.8.6/mkspecs/common/gcc-base-macx.conf \
		/usr/local/Cellar/qt/4.8.6/mkspecs/common/g++-base.conf \
		/usr/local/Cellar/qt/4.8.6/mkspecs/common/g++-macx.conf \
		/usr/local/Cellar/qt/4.8.6/mkspecs/qconfig.pri \
		/usr/local/Cellar/qt/4.8.6/mkspecs/modules/qt_webkit_version.pri \
		/usr/local/Cellar/qt/4.8.6/mkspecs/features/qt_functions.prf \
		/usr/local/Cellar/qt/4.8.6/mkspecs/features/qt_config.prf \
		/usr/local/Cellar/qt/4.8.6/mkspecs/features/exclusive_builds.prf \
		/usr/local/Cellar/qt/4.8.6/mkspecs/features/default_pre.prf \
		/usr/local/Cellar/qt/4.8.6/mkspecs/features/mac/default_pre.prf \
		/usr/local/Cellar/qt/4.8.6/mkspecs/features/debug.prf \
		/usr/local/Cellar/qt/4.8.6/mkspecs/features/default_post.prf \
		/usr/local/Cellar/qt/4.8.6/mkspecs/features/mac/default_post.prf \
		/usr/local/Cellar/qt/4.8.6/mkspecs/features/mac/x86_64.prf \
		/usr/local/Cellar/qt/4.8.6/mkspecs/features/mac/objective_c.prf \
		/usr/local/Cellar/qt/4.8.6/mkspecs/features/unix/opengl.prf \
		/usr/local/Cellar/qt/4.8.6/mkspecs/features/qt.prf \
		/usr/local/Cellar/qt/4.8.6/mkspecs/features/unix/thread.prf \
		/usr/local/Cellar/qt/4.8.6/mkspecs/features/moc.prf \
		/usr/local/Cellar/qt/4.8.6/mkspecs/features/shared.prf \
		/usr/local/Cellar/qt/4.8.6/mkspecs/features/warn_on.prf \
		/usr/local/Cellar/qt/4.8.6/mkspecs/features/mac/rez.prf \
		/usr/local/Cellar/qt/4.8.6/mkspecs/features/mac/sdk.prf \
		/usr/local/Cellar/qt/4.8.6/mkspecs/features/resources.prf \
		/usr/local/Cellar/qt/4.8.6/mkspecs/features/uic.prf \
		/usr/local/Cellar/qt/4.8.6/mkspecs/features/yacc.prf \
		/usr/local/Cellar/qt/4.8.6/mkspecs/features/lex.prf \
		/usr/local/Cellar/qt/4.8.6/mkspecs/features/include_source_dir.prf \
		/Users/jui-hsienwang/Library/Frameworks/QGLViewer.framework/QGLViewer.prl \
		/usr/local/Cellar/qt/4.8.6/lib/QtXml.framework/QtXml.prl \
		/usr/local/Cellar/qt/4.8.6/lib/QtCore.framework/QtCore.prl \
		/usr/local/Cellar/qt/4.8.6/lib/QtOpenGL.framework/QtOpenGL.prl \
		/usr/local/Cellar/qt/4.8.6/lib/QtGui.framework/QtGui.prl
	$(QMAKE) -spec /usr/local/Cellar/qt/4.8.6/mkspecs/macx-g++ -o Makefile dobashi.pro
/usr/local/Cellar/qt/4.8.6/mkspecs/common/unix.conf:
/usr/local/Cellar/qt/4.8.6/mkspecs/common/mac.conf:
/usr/local/Cellar/qt/4.8.6/mkspecs/common/gcc-base.conf:
/usr/local/Cellar/qt/4.8.6/mkspecs/common/gcc-base-macx.conf:
/usr/local/Cellar/qt/4.8.6/mkspecs/common/g++-base.conf:
/usr/local/Cellar/qt/4.8.6/mkspecs/common/g++-macx.conf:
/usr/local/Cellar/qt/4.8.6/mkspecs/qconfig.pri:
/usr/local/Cellar/qt/4.8.6/mkspecs/modules/qt_webkit_version.pri:
/usr/local/Cellar/qt/4.8.6/mkspecs/features/qt_functions.prf:
/usr/local/Cellar/qt/4.8.6/mkspecs/features/qt_config.prf:
/usr/local/Cellar/qt/4.8.6/mkspecs/features/exclusive_builds.prf:
/usr/local/Cellar/qt/4.8.6/mkspecs/features/default_pre.prf:
/usr/local/Cellar/qt/4.8.6/mkspecs/features/mac/default_pre.prf:
/usr/local/Cellar/qt/4.8.6/mkspecs/features/debug.prf:
/usr/local/Cellar/qt/4.8.6/mkspecs/features/default_post.prf:
/usr/local/Cellar/qt/4.8.6/mkspecs/features/mac/default_post.prf:
/usr/local/Cellar/qt/4.8.6/mkspecs/features/mac/x86_64.prf:
/usr/local/Cellar/qt/4.8.6/mkspecs/features/mac/objective_c.prf:
/usr/local/Cellar/qt/4.8.6/mkspecs/features/unix/opengl.prf:
/usr/local/Cellar/qt/4.8.6/mkspecs/features/qt.prf:
/usr/local/Cellar/qt/4.8.6/mkspecs/features/unix/thread.prf:
/usr/local/Cellar/qt/4.8.6/mkspecs/features/moc.prf:
/usr/local/Cellar/qt/4.8.6/mkspecs/features/shared.prf:
/usr/local/Cellar/qt/4.8.6/mkspecs/features/warn_on.prf:
/usr/local/Cellar/qt/4.8.6/mkspecs/features/mac/rez.prf:
/usr/local/Cellar/qt/4.8.6/mkspecs/features/mac/sdk.prf:
/usr/local/Cellar/qt/4.8.6/mkspecs/features/resources.prf:
/usr/local/Cellar/qt/4.8.6/mkspecs/features/uic.prf:
/usr/local/Cellar/qt/4.8.6/mkspecs/features/yacc.prf:
/usr/local/Cellar/qt/4.8.6/mkspecs/features/lex.prf:
/usr/local/Cellar/qt/4.8.6/mkspecs/features/include_source_dir.prf:
/Users/jui-hsienwang/Library/Frameworks/QGLViewer.framework/QGLViewer.prl:
/usr/local/Cellar/qt/4.8.6/lib/QtXml.framework/QtXml.prl:
/usr/local/Cellar/qt/4.8.6/lib/QtCore.framework/QtCore.prl:
/usr/local/Cellar/qt/4.8.6/lib/QtOpenGL.framework/QtOpenGL.prl:
/usr/local/Cellar/qt/4.8.6/lib/QtGui.framework/QtGui.prl:
qmake:  FORCE
	@$(QMAKE) -spec /usr/local/Cellar/qt/4.8.6/mkspecs/macx-g++ -o Makefile dobashi.pro

dobashi.app/Contents/PkgInfo: 
	@$(CHK_DIR_EXISTS) dobashi.app/Contents || $(MKDIR) dobashi.app/Contents 
	@$(DEL_FILE) dobashi.app/Contents/PkgInfo
	@echo "APPL????" >dobashi.app/Contents/PkgInfo
dobashi.app/Contents/Resources/empty.lproj: 
	@$(CHK_DIR_EXISTS) dobashi.app/Contents/Resources || $(MKDIR) dobashi.app/Contents/Resources 
	@touch dobashi.app/Contents/Resources/empty.lproj
	
dobashi.app/Contents/Info.plist: 
	@$(CHK_DIR_EXISTS) dobashi.app/Contents || $(MKDIR) dobashi.app/Contents 
	@$(DEL_FILE) dobashi.app/Contents/Info.plist
	@sed -e "s,@SHORT_VERSION@,1.0,g" -e "s,@TYPEINFO@,????,g" -e "s,@ICON@,,g" -e "s,@EXECUTABLE@,dobashi,g" -e "s,@TYPEINFO@,????,g" /usr/local/Cellar/qt/4.8.6/mkspecs/macx-g++/Info.plist.app >dobashi.app/Contents/Info.plist
dist: 
	@$(CHK_DIR_EXISTS) .tmp/dobashi1.0.0 || $(MKDIR) .tmp/dobashi1.0.0 
	$(COPY_FILE) --parents $(SOURCES) $(DIST) .tmp/dobashi1.0.0/ && $(COPY_FILE) --parents include/readsound.h include/sourcefunction.h include/streamsound.h include/ui_window.h parameters.h .tmp/dobashi1.0.0/ && $(COPY_FILE) --parents main.cpp src/sourcefunction.cpp src/streamsound.cpp src/ui_window.cpp .tmp/dobashi1.0.0/ && (cd `dirname .tmp/dobashi1.0.0` && $(TAR) dobashi1.0.0.tar dobashi1.0.0 && $(COMPRESS) dobashi1.0.0.tar) && $(MOVE) `dirname .tmp/dobashi1.0.0`/dobashi1.0.0.tar.gz . && $(DEL_FILE) -r .tmp/dobashi1.0.0


clean:compiler_clean 
	-$(DEL_FILE) $(OBJECTS)
	-$(DEL_FILE) *~ core *.core


####### Sub-libraries

distclean: clean
	-$(DEL_FILE) -r dobashi.app
	-$(DEL_FILE) Makefile


check: first

mocclean: compiler_moc_header_clean compiler_moc_source_clean

mocables: compiler_moc_header_make_all compiler_moc_source_make_all

compiler_objective_c_make_all:
compiler_objective_c_clean:
compiler_moc_header_make_all: moc_ui_window.cpp
compiler_moc_header_clean:
	-$(DEL_FILE) moc_ui_window.cpp
moc_ui_window.cpp: include/streamsound.h \
		include/ui_window.h \
		include/sourcefunction.h \
		include/ui_window.h
	/usr/local/Cellar/qt/4.8.6/bin/moc $(DEFINES) $(INCPATH) -D__APPLE__ -D__GNUC__ include/ui_window.h -o moc_ui_window.cpp

compiler_rcc_make_all:
compiler_rcc_clean:
compiler_image_collection_make_all: qmake_image_collection.cpp
compiler_image_collection_clean:
	-$(DEL_FILE) qmake_image_collection.cpp
compiler_moc_source_make_all:
compiler_moc_source_clean:
compiler_rez_source_make_all:
compiler_rez_source_clean:
compiler_uic_make_all:
compiler_uic_clean:
compiler_yacc_decl_make_all:
compiler_yacc_decl_clean:
compiler_yacc_impl_make_all:
compiler_yacc_impl_clean:
compiler_lex_make_all:
compiler_lex_clean:
compiler_clean: compiler_moc_header_clean 

####### Compile

main.o: main.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o main.o main.cpp

sourcefunction.o: src/sourcefunction.cpp parameters.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o sourcefunction.o src/sourcefunction.cpp

streamsound.o: src/streamsound.cpp parameters.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o streamsound.o src/streamsound.cpp

ui_window.o: src/ui_window.cpp parameters.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o ui_window.o src/ui_window.cpp

moc_ui_window.o: moc_ui_window.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_ui_window.o moc_ui_window.cpp

####### Install

install:   FORCE

uninstall:   FORCE

FORCE:

