#include <stdio.h>
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "realsense.h"


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
    int xL_max = 0, xL_min, yL_max = 0, yL_min, x_width = 0, depth = 0;

    while(true) {
		camera.getColorFrame(img);	// capture color frame

        width = img.cols;
        height = img.rows;

		cv::cvtColor(img, gry_img, cv::COLOR_BGR2GRAY);	
        cv::inRange(gry_img, threshold_value, 255, dst_img);
        cv::imshow("dst_img0", dst_img);

        cv::erode(dst_img, dst_img, cv::Mat(), cv::Point(-1, -1), 2);
        cv::imshow("dst_img1", dst_img);

        std::vector<std::vector<cv::Point>> contours;
        cv::findContours(dst_img, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_NONE);
        std::vector<std::vector<cv::Point>> contours_subset;
        double max_area = 0;
        int max_area_number = -1;
        for (int i = 0; i < contours.size(); i++) {
            double area = contourArea(contours.at(i));
            if (area > max_area) {       /* 変更 */
                max_area = area;
                max_area_number = i;
            }
        }

        if(max_area < 2000) {
            throw std::runtime_error("No obstacles.");
        }

        contours_subset.push_back(contours.at(max_area_number));

        dst_img = cv::Mat::zeros(dst_img.rows, dst_img.cols, CV_8UC1);
        drawContours(dst_img, contours_subset, 0, cv::Scalar(255), -1);

        xL_min = width;
        yL_min = height;

        for (yL = 0; yL < height; yL++) {
            for (xL = 0; xL < width; xL++) {
                if(xL < width / 4) {
                    dst_img.at<uchar>(yL, xL) = 0;
                }
                if (dst_img.at<uchar>(yL, xL) == 255) {
                    if (xL > xL_max) {
                        xL_max = xL;
                    }
                    if (yL > yL_max) {
                        yL_max = yL;
                    }

                    if (xL < xL_min) {
                        xL_min = xL;
                    }
                    if (yL < yL_min) {
                        yL_min = yL;
                    }
                }
            }
        }

        rectangle(img, cv::Point(xL_min, yL_min), cv::Point(xL_max, yL_max), cv::Scalar(0, 255, 0), 1, 8);
        circle(img, cv::Point(xL_min, yL_min), 1, cv::Scalar(0, 0, 255), -1);
        circle(img, cv::Point(xL_min, yL_min), 8, cv::Scalar(0, 0, 255));

        cv::imshow("img", img);
        cv::imshow("dst_img2", dst_img);

		std::array<float, 3> min_point = camera.doDeprojectPosition(dph_img, xL_min, yL_min);
        std::array<float, 3> max_point = camera.doDeprojectPosition(dph_img, xL_max, yL_max);

        if(min_point.point[2] < 1.0) {
            x_width = max_point.point[0] - min_point.point[0];
            depth = max_point.point[2];
            break;
        }

        if(cv::waitKey(10) == 27){					    // waiting 'esc' key input
            cv::destroyAllWindows();					// close all windows
            break;
        }	
	}

    return {x_width, depth};
}

/*　画像座標系→ワールド座標系
    point[] depth 1m未満になったら差分を出す　*/


