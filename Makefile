CC = g++

TARGETS = main.cpp cpputils/graphics/image.cc

OBJS = image.o Orientation.o main.o

SUBSET_CFLAGS = -std=c++17 -Wall 

CFLAGS = $(SUBSET_CFLAGS) -lm -I/opt/X11/include -lpthread -lX11 -lstdc++ -I/usr/X11R6/include -L/usr/X11R6/lib

RC_FILES= RC.hpp RC.cpp RCVisualizer.hpp RCVisualizer.cpp

all: main.exe

main.exe: $(OBJS)
	$(CC) $(CFLAGS) -o main.exe $(OBJS)

main.o: $(RC_FILES)
	$(CC) $(SUBSET_CFLAGS) -o main.o -c main.cpp

image.o:
	$(CC) $(CFLAGS) -o image.o -c cpputils/graphics/image.cc

#RCVisualizer.o:
#	$(CC) $(SUBSET_CFLAGS) -o RCVisualizer.o -c RCVisualizer.cpp

Orientation.o:
	$(CC) $(SUBSET_CFLAGS) -o Orientation.o -c Orientation.h

run: main.exe
	./main.exe

clean: 
	rm *.o *.exe