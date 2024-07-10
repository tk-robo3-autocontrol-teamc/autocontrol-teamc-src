#include <stdio.h>
#include <iostream>
#include <tuple>
#include <opencv2/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "realsense.h"

int x_width;
float depth;

std::tuple<int, float> getObstacleData() {
    return std::make_tuple(1, 3.14);
}

int main(int argc, char **argv){
    rs2::config cfg;
	cfg.enable_stream(RS2_STREAM_COLOR, WIDTH, HEIGHT, RS2_FORMAT_BGR8, FPS);   // Color
	cfg.enable_stream(RS2_STREAM_DEPTH, WIDTH, HEIGHT, RS2_FORMAT_Z16, FPS);    // Depth
	rs2::align align(RS2_STREAM_DEPTH);						// Align color stream to depth stream
	
	RsCamera camera(cfg, align);									// create instance
	
	cv::Mat img(cv::Size(WIDTH, HEIGHT), CV_8UC3);			// define image
	cv::Mat dph_img(cv::Size(WIDTH, HEIGHT), CV_8UC3);	// define image	
    cv::Mat gry_img, dst_img;
    int height, width;
    int threshold_value = 150;
    int xL, yL;
    int xL_max = 0, xL_min, yL_max = 0, yL_min, x_width = 0;

    while(true) {
		camera.getColorFrame(img);	// capture color frame

        width = img.cols;
        height = img.rows;

		cv::cvtColor(img, gry_img, cv::COLOR_BGR2GRAY);	
        cv::inRange(gry_img, threshold_value, 255, dst_img);
        cv::imshow("dst_img0", dst_img);

        for (yL = 0; yL < height; yL++) {
            for (xL = 0; xL < width; xL++) {
                if(xL < width/4) {
                    dst_img.at<uchar>(yL, xL) = 0;
                }

                if(xL > width * 3/4) {
                    dst_img.at<uchar>(yL, xL) = 0;
                }

                if(yL < height / 4) {
                    dst_img.at<uchar>(yL, xL) = 0;
                }
           
            } 
        }

        cv::erode(dst_img, dst_img, cv::Mat(), cv::Point(-1, -1), 2);
        cv::imshow("dst_img1", dst_img);

        xL_min = width;

        for (yL = 0; yL < height; yL++) {
            for (xL = 0; xL < width; xL++) {
                if(xL < width/4) {
                    dst_img.at<uchar>(yL, xL) = 0;
                }

                if(xL > width * 3/4) {
                    dst_img.at<uchar>(yL, xL) = 0;
                }

                if(yL < height / 4) {
                    dst_img.at<uchar>(yL, xL) = 0;
                }
            } 
        }

        for (int yL = height - 1; yL >= 0; yL--) {
            for (int xL = width - 1; xL >= 0; xL--) {
                if (dst_img.at<uchar>(yL, xL) == 255 && min_point[2] < 1.0) {
                    if (xL_max == -1) {
                        xL_max = xL;
                    }
                    if (xL < xL_min) {
                        xL_min = xL;
                    }
                }
            }
        }

        std::array<float, 3> min_point = camera.doDeprojectPosition(dph_img, xL_min, yL_min);
        std::array<float, 3> max_point = camera.doDeprojectPosition(dph_img, xL_max, yL_max);


        if (xL_max != -1 && xL_min != INT_MAX && min_point[2] < 1.0) {
            x_width = xL_max - xL_min;
            depth = min_point[2];
        } else {
            x_width = 0;  
            depth = 0;
            std::cout << "No obstacle" << std::endl;
        }

        auto [x_width, depth] = getObstacleData();
        std::cout << "xL_max：" << xL_max << "xL_min：" << xL_min << std::endl;
        std::cout << "x_width：" << x_width << "depth：" << depth << std::endl;
		
        char windowName[] = "depth_camera";
        while (camera.read(img)) {
            imshow(windowName, img);
            const int key = cv::waitKey(1);
            if(key == 'q') {
                break;
            } else if(key == 's') { 
                if (exist_file(file_name)) {
                    puts("file exists");
                    sprintf(file_name, "img%d.png", ++file_number); 
                    cv::imwrite(file_name, img);
                    cv::imwrite(file_name, dst_img);
                } else {
                    puts("file isn't exists");
                    cv::imwrite(file_name, img);
                    cv::imwrite(file_name, dst_img);
                }
            }
        }

        if(cv::waitKey(10) == 27){					    // waiting 'esc' key input
            cv::destroyAllWindows();					// close all windows
            break;
        }	

        cv::imshow("img", img);
        cv::imshow("dst_img2", dst_img);
	}

    return 0;
}

