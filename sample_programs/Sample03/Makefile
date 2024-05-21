CC		= g++
CFLAGS	= -Wall -O2
TARGET	= main
INCDIR	=
LIBDIR	= -I /usr/local
LIBS	= -lm

$(TARGET): main.o car.o
	$(CC) -o $@ main.o car.o $(CFLAGS) $(LIBDIR) $(LIBS)

main.o: main.cpp
	$(CC) -c main.cpp $(CFLAGS) $(LIBDIR) $(LIBS)

car.o: car.cpp
	$(CC) -c car.cpp $(CFLAGS) $(LIBDIR) $(LIBS)

clean:
	rm -f $(TARGET) *.o