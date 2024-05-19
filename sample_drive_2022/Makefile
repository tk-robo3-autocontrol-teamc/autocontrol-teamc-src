# Makefile
CC     = g++
CFLAGS = -Wall -O2
TARGET = sample_main
INCDIR = 
LIBDIR = 
LIBS   = -lEposCmd


$(TARGET):sample_main.o drv_fnc.o
	$(CC) -o sample_main sample_main.o drv_fnc.o $(CFLAGS) $(LIBS)
	
sample_main.o:sample_main.cpp
	$(CC) -c sample_main.cpp
		
drv_fnc.o:drv_fnc.cpp
	$(CC) -c drv_fnc.cpp
		
clean:
	rm -f $(TARGET) *.o
