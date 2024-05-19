# Makefile
CC     = g++
CFLAGS = -Wall -O2
TARGET = sample_main
INCDIR = 
LIBDIR = 
LIBS   = ../YDLidar-SDK-master/lib/libydl.so

$(TARGET): sample_main.o lidar.o
	$(CC) -o sample_main sample_main.o lidar.o $(CFLAGS) $(LIBS)

sample_main.o:sample_main.cpp
	$(CC) -c sample_main.cpp

lidar.o:lidar.cpp
	$(CC) -c lidar.cpp


clean:
	rm -f sample_main *.o
	
	
