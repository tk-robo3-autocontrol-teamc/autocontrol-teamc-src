CC	    = g++
CFLAGS	= -Wall -O2
TARGET	= sample_main
INCDIR	=
LIBDIR	= -I /usr/include/opencv4/
LIBS	= -std=c++11 -lopencv_core -lopencv_highgui -lopencv_imgcodecs -lopencv_imgproc -lopencv_videoio

$(TARGET): sample_main.cpp
	$(CC) -o sample_main sample_main.cpp $(CFLAGS) $(LIBDIR) $(LIBS)

clean:
	rm -f $(TARGET) *.o
