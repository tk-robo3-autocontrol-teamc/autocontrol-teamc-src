#/sample_depth_cam/Makefile

CC 	 = g++
CFLAGS   = -Wall -O2 -std=c++11
TARGET   = sample_main
INCDIR	 = 
LDFLAGS  = -I /usr/local/include/librealsense2
LDFLAGS2 = -I /usr/include/opencv4
LIBS     = -lrealsense2 -latomic
LIBS2    = -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_imgcodecs

$(TARGET): sample_main.o realsense.o
	$(CC) -o $@ sample_main.o realsense.o $(LDFLAGS) $(LIBS) $(CFLAGS) $(LDFLAGS2) $(LIBS2)
	
sample_main.o: sample_main.cpp
	$(CC) -c sample_main.cpp $(CFLAGS) $(LDFLAGS2) $(LIBS2)
	
realsense.o: realsense.cpp
	$(CC) -c realsense.cpp $(CFLAGS) $(LDFLAGS2) $(LIBS2)
	
clean:
	rm $(TARGET) *.o

	
