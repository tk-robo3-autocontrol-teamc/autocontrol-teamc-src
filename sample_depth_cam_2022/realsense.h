// realsense-test_06 --- 2022.04.19
#ifndef _REALSENSE_H_
#define _REALSENSE_H_

#include <iostream>
#include <librealsense2/rs.hpp> // Include RealSense Cross Platform API
#include <librealsense2/rsutil.h>
#include <opencv2/opencv.hpp>	// opencv
#include <opencv2/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#define WIDTH 	640 // horizontal image size
#define HEIGHT	480 // vertical image size
#define FPS 	30  	// frame rate 


class RsCamera
{
public:
  float point[3];


  // Constructor
  RsCamera(rs2::config cfg, rs2::align _align);
  // Destructor
  ~RsCamera();

  void getColorFrame(cv::Mat& color_image);
  void doDeprojectPosition(cv::Mat& depth_image, int x_pix, int y_pix);
  

private:
  // Create a Pipeline - this serves as a top-level API for streaming and processing frames
  rs2::pipeline pipe;
  
  rs2::colorizer color_map;
  
  bool isConnectedDevices();
  rs2::context ctx;
  rs2::device_list devices;
  
  rs2::align align = rs2::align(RS2_STREAM_DEPTH);
  rs2_intrinsics intr;
    
};

#endif // _REALSENSE_H_


