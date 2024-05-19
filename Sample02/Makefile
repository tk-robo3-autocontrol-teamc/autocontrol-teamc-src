CC     = g++
CFLAGS = -Wall -O2
TARGET = main
INCDIR = 
LIBDIR = -I /usr/local
LIBS   = -lm

$(TARGET): main.o fnc.o
	$(CC) -o main main.o fnc.o $(CFLAGS) $(LIBDIR) $(LIBS)
	
main.o:main.c
	$(CC) -c main.c

fnc.o:fnc.c
	$(CC) -c fnc.c
		
clean:
	rm -f $(TARGET) *.o
