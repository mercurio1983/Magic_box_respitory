#
#
#
#delay:  stereoviewGL_delay.c questionare.c tools.c
		#$(CC) -o  stereoviewGL_delay tools.c questionare.c stereoviewGL_delay.c -I. -lstdc++ $(LIBFLAGS) $(SDLFLAGS)  

#TARGET = liblabjackusb.so.2.0.3
#TARGET =
#DESTINATION = /usr/local/lib
#
#HEADER = globals.h
#HEADER_DESTINATION = /usr/local/include

INCLUDES = -I/home/ehrssonlab/public-stereo/avt/lib
#INCLUDES = -I/home/mercurio/avt/lib


CFLAGS += -Wall -O2 
CFLAGS2 += -Wall 
LIBFLAGS = -ldc1394 -lGL -lGLU -L/usr/include -L/usr/X11R6/lib -lX11 -lXext -lXv -lXi -lm -lpthread -L/usr/local/include -lcudart -L/home/ehrssonlab/public-stereo/avt/lib #-lXmu
LIBFLAGS2 = -lavformat -lavcodec
LIBFLAGS3 = -L/usr/local/include -lavformat -lavcodec -lavutil #-lz -lm
LIBFLAGS4 = `pkg-config --libs opencv`
LIBFLAGS5 = -L/usr/bin -I/usr/include -L/usr/lib -lcudart
LIBFLAGS6 = -Llib -lnvstusb -lGL -lGLU -lglut -lX11 -lXxf86vm -lpthread -lusb-1.0

CFLAGS2=-Wall -Werror -g -ansi -pedantic -std=c89
CCFLAGS2=-Wall -Werror -g
CCPFLAGS2 = -Wall `pkg-config --cflags opencv`
LDFLAGS=-g -Wall -lstdc++

SDLFLAGS= `sdl-config --cflags --libs`
SDLFLAGS2= `sdl-config --libs`
CC = gcc
CC2 = g++
#NV = /usr/local/cuda/bin/nvcc
NV = /usr/bin/nvcc
#node.o queue4.o
#OBJS1 = stereoviewGL_delay.o questionare.o tools.o
OBJS2 = queue_Wrapper.o
OBJS3 = image_lr.o node.o queue4.o

OBJS8 = stereoviewGL_delay3D.o rendering.o tools.o
OBJS82 = stereoviewGL_delay3D_version2.o rendering.o tools.o
#OBJS4 = stereoviewGL_delay2.o questionare.o tools.o
#OBJS5 = stereoviewGL_delay.o questionare.o tools.o
OBJS6 = image.o
OBJSTEST = test_queue.o
SOURCE1 = stereoviewGL_delay.c rendering.c tools.c
SOURCETEST = test_queue.c
SOURCE2 = queue_Wrapper.cc
SOURCE3 = image_lr.cpp node.cpp queue4.cpp
SOURCE6 = image.cpp

OBJS7 = gpu_bayer.o
SOURCE7 = gpu_bayer.cu

SOURCE8 = stereoviewGL_delay3D.c rendering.c tools.c
SOURCE82 = stereoviewGL_delay3D_version2.c rendering.c tools.c
#SOURCE4 = stereoviewGL_delay2.c questionare.c tools.c
#SOURCE5 = stereoviewGL_delay.c questionare.c tools.c
#PROG = stereoviewGL_delay
#PROG2 = stereoviewGL_delay2
PROG3 = stereoviewGL_delay3D
PROG32 = stereoviewGL_delay3D_version2

$(OBJS8): $(SOURCE8) 
	$(CC) $(CFLAGS) $(INCLUDES) -c $(SOURCE8) -I. $(LIBFLAGS) $(SDLFLAGS)

$(OBJS82): $(SOURCE82) 
	$(CC) $(CFLAGS) $(INCLUDES) -c $(SOURCE82) -I. $(LIBFLAGS) $(SDLFLAGS)

$(OBJS7): $(SOURCE7) 
	$(NV) --verbose -c $(SOURCE7) -I. $(LIBFLAGS5) $(LIBFLAGS4)

$(OBJS6): $(SOURCE6) 
	$(CC) $(CCPFLAGS2) --verbose -c $(SOURCE6) -I. $(LIBFLAGS4) 

#$(OBJS4): $(SOURCE4) 
#	$(CC) $(CFLAGS) -c $(SOURCE4) -I. $(LIBFLAGS) $(SDLFLAGS)

$(OBJS3): $(SOURCE3) 
	$(CC) $(CCPFLAGS2) -c $(SOURCE3) -I. $(LDFLAGS)

$(OBJS2): $(SOURCE2)
	$(CC) $(CCFLAGS2) -c $(SOURCE2) -I. $(LDFLAGS) 

#$(OBJS1): $(SOURCE1)
#	$(CC) $(CFLAGS) -c $(SOURCE1) -I. $(LIBFLAGS) $(SDLFLAGS)

#$(OBJS5): $(SOURCE5)
#	$(CC) $(CFLAGS) -c $(SOURCE5) -I. $(LIBFLAGS) $(SDLFLAGS)



#$(PROG): $(OBJS3) $(OBJS2) $(OBJS1) 
	#$(CC) $(OBJS3) $(OBJS2) $(OBJS1) -o  $(PROG) -I. $(LIBFLAGS) $(SDLFLAGS) $(LDFLAGS)
	

$(OBJSTEST): $(SOURCETEST)
	$(CC) $(CFLAGS) -c $(SOURCETEST) 

#$(PROG2): $(OBJS3) $(OBJS2) $(OBJS4) $(OBJS6) $(OBJS7)
#	$(CC) $(OBJS3) $(OBJS2) $(OBJS4) $(OBJS6) $(OBJS7) -o  $(PROG2) -I.  $(LIBFLAGS5) $(LIBFLAGS4) $(LIBFLAGS) $(SDLFLAGS) $(LDFLAGS)

#$(PROG2): $(OBJS3) $(OBJS2) $(OBJS4) $(OBJS6) 
#	$(CC) $(OBJS3) $(OBJS2) $(OBJS4) $(OBJS6) -o  $(PROG2) -I.  $(LIBFLAGS5) $(LIBFLAGS4) $(LIBFLAGS) $(SDLFLAGS) $(LDFLAGS)

#$(PROG3): $(OBJS4) $(OBJS3) $(OBJS2) $(OBJSTEST)
#	$(CC) $(OBJS4) $(OBJS3) $(OBJS2) $(OBJSTEST) -o  $(PROG3) -I. $(LDFLAGS) 

$(PROG3): lib/libnvstusb.a $(OBJS3) $(OBJS2) $(OBJS8) $(OBJS6) $(OBJS7) 
	$(CC) $(OBJS3) $(OBJS2) $(OBJS8) $(OBJS6) $(OBJS7) -o  $(PROG3) -I. $(LIBFLAGS6)  $(LIBFLAGS5) $(LIBFLAGS4) $(LIBFLAGS3) $(LIBFLAGS) $(SDLFLAGS) $(LDFLAGS)

$(PROG32): lib/libnvstusb.a $(OBJS3) $(OBJS2) $(OBJS82) $(OBJS6) $(OBJS7) 
	$(CC) $(OBJS3) $(OBJS2) $(OBJS82) $(OBJS6) $(OBJS7) -o  $(PROG32) -I. $(LIBFLAGS6)  $(LIBFLAGS5) $(LIBFLAGS4) $(LIBFLAGS3) $(LIBFLAGS) $(SDLFLAGS) $(LDFLAGS)

%.o: %.c

#	$(CC) $(CFLAGS) -c $<

#all: test.c camera.c definitions.c testSDL.c
# $(CC) -o test test.c camera.c definitions.c -I. $(LIBFLAGS)
# $(CC) -o testSDL testSDL.c camera.c definitions.c -I. $(LIBFLAGS) $(SDLFLAGS)

#cuda: conv.cu
#	$(NV) -c *cu
#	$(CC) *o -o cuda_multiview $(LIBFLAGS)

#all: avt_singleview.c dc1394_multiview.c
# $(CC) -o test test.c camera.c definitions.c -I. $(LIBFLAGS)
#	$(CC) -o avt_singleview-new avt_singleview.c -I. $(LIBFLAGS)
#	$(CC) -o dc1394_multiview dc1394_multiview.c -I. $(LIBFLAGS)

#delay: $(PROG)

#delay2: $(PROG2)

all: delay3 delay32

delay3: $(PROG3)

delay32: $(PROG32)

lib/libnvstusb.a: 
		make -C lib

clean: clean_delay3 clean_delay32

#clean_delay:
	#rm *.o $(PROG)
	
clean_delay3:
	rm *.o $(PROG3)
	
clean_delay32:
	rm *.o $(PROG32)
