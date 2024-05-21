# Makefile
CC     = g++
CFLAGS = -Wall -O2
TARGET = sample_main
INCDIR = 
LIBDIR = 
LIBS   = 


$(TARGET):sample_main.o func.o
	$(CC) -o sample_main sample_main.o func.o $(CFLAGS) $(LIBS)
	
sample_main.o:sample_main.cpp
	$(CC) -c sample_main.cpp
		
func.o:func.cpp
	$(CC) -c func.cpp
		
clean:
	rm -f $(TARGET) *.o
