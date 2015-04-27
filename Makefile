INCLUDE=-I/Users/jui-hsienwang/portaudio/portaudio/include \
		-I/Users/jui-hsienwang/portaudio/portaudio/src/common \
		-I/usr/local/Cellar/eigen/3.2.2/include/eigen3 \
		-I./include \
		-I./
LIBS=/Users/jui-hsienwang/portaudio/portaudio/lib/.libs/libportaudio.a \
	 -lsndfile

FRAMEWORK=-framework CoreAudio \
		  -framework AudioUnit \
		  -framework AudioToolbox \
		  -framework Carbon

all: dobashi 

dobashi : main.o streamsound.o 
	g++ main.o streamsound.o -o dobashi ${INCLUDE} ${LIBS} ${FRAMEWORK}

streamsound.o : streamsound.cpp ./include/streamsound.h
	g++ -c streamsound.cpp ${INCLUDE}

main.o: main.cpp ./include/*.h 
	g++ -c main.cpp ${INCLUDE}

clean : 
	rm *.o dobashi

