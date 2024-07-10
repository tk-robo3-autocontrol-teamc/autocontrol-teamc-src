#include <stdio.h>
#include <opencv2/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>
#include <opencv2/imgproc/imgproc.hpp>


int main(void)
{
    cv::Mat img;
    cv::Mat gry_img, dst_img;
    int height, width;
    int msk_th_min = 125, msk_th_max = 150;
    int xL, yL;
    int xL_max = 0, xL_min, yL_max = 0, yL_min;

    img = cv::imread("img_211208_3.png", 1);
    height = img.rows;
    width = img.cols;
    cv::imshow("img_org", img);

    cv::cvtColor(img, gry_img, cv::COLOR_BGR2GRAY);
    cv::inRange(gry_img, msk_th_min, msk_th_max, dst_img);
    cv::imshow("dst_img0", dst_img);
    cv::erode(dst_img, dst_img, cv::Mat(), cv::Point(-1, -1), 2);

    cv::imshow("dst_img1", dst_img);
    std::vector<std::vector<cv::Point>> contours;
    cv::findContours(dst_img, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_NONE);
    std::vector<std::vector<cv::Point>> contours_subset;
    for (int i = 0; i < contours.size(); i++) {
        double area = contourArea(contours.at(i));
        if (area > 1000 && area < 1500) {
            contours_subset.push_back(contours.at(i));
        }
    }

    dst_img = cv::Mat::zeros(dst_img.rows, dst_img.cols, CV_8UC1);
    drawContours(dst_img, contours_subset, 0, cv::Scalar(255), -1);

    xL_min = width;
    yL_min = height;
    
    for (yL = 0; yL < height; yL++) {
        for (xL = 0; xL < width; xL++) {
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
    cv::imshow("gry_img", gry_img);
    cv::imshow("dst_img2", dst_img);

    cv::waitKey(0);

    return 0;
}

#include <stdio.h>
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>
#include <opencv2/imgproc/imgproc.hpp>

int main(void) {
    cv::Mat img;
    cv::Mat gry_img, dst_img;
    int height, width;
    int threshold_value = 125;
    int xL, yL;
    int xL_max = -1, xL_min = INT_MAX;

    img = cv::imread("img9.png", 1);
    height = img.rows;
    width = img.cols;

    cv::imshow("img_org", img);
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

    xL_min = width;

    for (int yL = height - 1; yL >= 0; yL--) {
        for (int xL = width - 1; xL >= 0; xL--) {
            if (dst_img.at<uchar>(yL, xL) == 255) {
                if (xL_max == -1) {
                    xL_max = xL;
                }
                if (xL < xL_min) {
                    xL_min = xL;
                }
            }
        }
    }

    int x_width = xL_max - xL_min;
    // xL_maxとxL_minが初期値でないことを確認
    if (xL_max != -1 && xL_min != INT_MAX && xL_max - xL_min < 100) {
        x_width = xL_max - xL_min;
    } else {
        x_width = 0;  
        std::cerr << "No obstacle or too close to the obstacle." << std::endl;
    }

    std::cout << xL_max << std::endl;
    std::cout << xL_min << std::endl;
    std::cout << x_width << std::endl;

    cv::imshow("img", img);
    cv::imshow("gry_img", gry_img);
    cv::imshow("dst_img2", dst_img);

    cv::waitKey(0);

    return 0;
}