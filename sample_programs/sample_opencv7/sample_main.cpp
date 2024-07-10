// sample_depth_cam --- 2022.05.18
#include <iostream>             
#include "realsense.h"

using namespace std;

int main(int argc, char **argv){
	
	rs2::config cfg;
	cfg.enable_stream(RS2_STREAM_COLOR, WIDTH, HEIGHT, RS2_FORMAT_BGR8, FPS);   // Color
	cfg.enable_stream(RS2_STREAM_DEPTH, WIDTH, HEIGHT, RS2_FORMAT_Z16, FPS);    // Depth
	rs2::align align(RS2_STREAM_DEPTH);						// Align color stream to depth stream
	
	RsCamera camera(cfg, align);									// create instance
	
	cv::Mat img(cv::Size(WIDTH, HEIGHT), CV_8UC3);			// define image
	cv::Mat dph_img(cv::Size(WIDTH, HEIGHT), CV_8UC3);	// define image
	cv::Mat gry_img(cv::Size(WIDTH, HEIGHT), CV_8U); 		// define image
	cv::Mat prc_img(cv::Size(WIDTH, HEIGHT), CV_8U);		// define image

	
	while(true)
	{
		camera.getColorFrame(img);	// capture color frame
		
// image processing	-------------------------------------------	
		// convert gray scale image
		cv::cvtColor(img, gry_img, cv::COLOR_BGR2GRAY);	

		// invert brightness
		for(int y=0; y < HEIGHT; y++){
			for(int x=0; x < WIDTH; x++){
				prc_img.at<uchar>(y, x) = 255 - gry_img.at<uchar>(y, x);
			}	
		}

		// change image coordinate to world coordinate
		camera.doDeprojectPosition(dph_img, WIDTH/2, HEIGHT/2);
// image processing	-------------------------------------------	


		// Display image
		cv::imshow("COLOE_FRAME", img);			// display image
		cv::imshow("GRAY_FRAME", gry_img);	// display image
		cv::imshow("PRC_FRAME", prc_img);		// display image
		cv::imshow("DEPTH_FRAME", dph_img);	// display image
		
		if(cv::waitKey(10) == 27){					// waiting 'esc' key input
			cv::destroyAllWindows();					// close all windows
			break;
		}	
	}
	
	return EXIT_SUCCESS;
} 