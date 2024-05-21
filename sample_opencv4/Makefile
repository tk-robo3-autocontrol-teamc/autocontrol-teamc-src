CC		= g++
CFLAGS	= -Wall -O2
TARGET	= sample_main
INCDIR	=
LIBDIR	= -I /usr/include/opencv4/
LIBS	= -std=c++11 -lopencv_core -lopencv_highgui -lopencv_imgcodecs -lopencv_imgproc

$(TARGET): sample_main.o img_prc.o
	$(CC) -o $@ sample_main.o img_prc.o $(CFLAGS) $(LIBDIR) $(LIBS)

sample_main.o: sample_main.cpp
	$(CC) -c sample_main.cpp $(CFLAGS) $(LIBDIR) $(LIBS)

img_prc.o: img_prc.cpp
	$(CC) -c img_prc.cpp $(CFLAGS) $(LIBDIR) $(LIBS)

clean:
	rm -f $(TARGET) *.o