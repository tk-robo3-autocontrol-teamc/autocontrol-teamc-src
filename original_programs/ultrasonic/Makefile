CC		= g++
CFLAGS	= -Wall -O2
TARGET	= sample_main
INCDIR	=
LIBDIR	=
LIBS	= -std=c++11 -lwiringPi

$(TARGET): sample_main.o hc_sr04.o
	$(CC) -o $@ sample_main.o hc_sr04.o $(CFLAGS) $(LIBDIR) $(LIBS)

sample_main.o: sample_main.cpp
	$(CC) -c sample_main.cpp

hc_sr04.o: hc_sr04.cpp
	$(CC) -c hc_sr04.cpp

clean:
	rm -f $(TARGET) *.o
