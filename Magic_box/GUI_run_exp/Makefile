
CC = gcc
CFLAGS = -Wall
LIBFLAGS =  -lstdc++ -g
SDLFLAGS = `wx-config --cxxflags` `wx-config --libs`
SOURCES = run_exp.cpp run_GUI.cpp
OBJECTS = run_exp.o run_GUI.o
PROGRAM = run_exp

SOURCES2 = run_exp_3.cpp run_GUI_3.cpp
OBJECTS2 = run_exp_3.o run_GUI_3.o
PROGRAM2 = run_exp_version2

SOURCE1 = test_call_prog.cpp
OBJECT1 = test_call_prog.o
PROGRAM1 = test_call_prog

$(OBJECTS): $(SOURCES)
	$(CC) $(CFLAGS) -c $(SOURCES) -I. $(LIBFLAGS) $(SDLFLAGS)
 
$(PROGRAM): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(PROGRAM) -I. $(LIBFLAGS) $(SDLFLAGS)

$(OBJECTS2): $(SOURCES2)
	$(CC) $(CFLAGS) -c $(SOURCES2) -I. $(LIBFLAGS) $(SDLFLAGS)
 
$(PROGRAM2): $(OBJECTS2)
	$(CC) $(OBJECTS2) -o $(PROGRAM2) -I. $(LIBFLAGS) $(SDLFLAGS)

$(OBJECT1): $(SOURCE1)
	$(CC) $(CFLAGS) -c $(SOURCE1) -I. $(LIBFLAGS)
 
$(PROGRAM1): $(OBJECT1)
	$(CC) $(OBJECT1) -o $(PROGRAM1) -I. $(LIBFLAGS)
	
all: $(PROGRAM)

program: $(PROGRAM2)

test: $(PROGRAM1)

clean:
	rm run_exp.o run_GUI.o run_exp
