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

int main(){
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

        // std::vector<std::vector<cv::Point>> contours;
        // cv::findContours(dst_img, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_NONE);
        // std::vector<std::vector<cv::Point>> contours_subset;
        // double max_area = 0;
        // int max_area_number = -1;
        // for (double i = 0; i < contours.size(); i++) {
        //     double area = contourArea(contours.at(i));
        //     if (area > max_area) {       /* 変更 */
        //         max_area = area;
        //         max_area_number = i;
        //     }
        // }

        // if(max_area < 2000) {
        //     throw std::runtime_error("No obstacles.");
        // }

        // contours_subset.push_back(contours.at(max_area_number));

        // dst_img = cv::Mat::zeros(dst_img.rows, dst_img.cols, CV_8UC1);
        // drawContours(dst_img, contours_subset, 0, cv::Scalar(255), -1);

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

        // rectangle(img, cv::Point(xL_min, yL_min), cv::Point(xL_max, yL_max), cv::Scalar(0, 255, 0), 1, 8);
        // circle(img, cv::Point(xL_min, yL_min), 1, cv::Scalar(0, 0, 255), -1);
        // circle(img, cv::Point(xL_min, yL_min), 8, cv::Scalar(0, 0, 255));

		
        if(cv::waitKey(10) == 27){					    // waiting 'esc' key input
            cv::destroyAllWindows();					// close all windows
            break;
        }	

        cv::imshow("img", img);
        cv::imshow("dst_img2", dst_img);

	}

    return 0;
}

