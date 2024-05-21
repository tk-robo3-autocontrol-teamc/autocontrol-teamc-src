CC     = g++
CFLAGS = -Wall -O2
TARGET = sample_main
INCDIR = 
LIBDIR = -I /usr/local
LIBS   = -lm -lwiringPi

$(TARGET): sample_main.o
	$(CC) -o sample_main sample_main.o $(CFLAGS) $(LIBDIR) $(LIBS)
	
sample_main.o:sample_main.cpp
	$(CC) -c sample_main.cpp
		
clean:
	rm -f $(TARGET) *.o
