CC     = g++
CFLAGS = -Wall -O2
TARGET = main
INCDIR = 
LIBDIR = -I /usr/local
LIBS   = -lm

$(TARGET): main.o
	$(CC) -o main main.o $(CFLAGS) $(LIBDIR) $(LIBS)
	
main.o:main.c
	$(CC) -c main.c
		
clean:
	rm -f $(TARGET) *.o
