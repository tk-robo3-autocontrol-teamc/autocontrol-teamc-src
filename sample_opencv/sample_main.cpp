#include <stdio.h>
#include <opencv2/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>
#include <opencv2/imgproc/imgproc.hpp>

int main(void)
{
    cv::Mat img;
    int height, width;

    img = cv::imread("img_211208_3.bmp", 1);
    height = img.rows;
    width = img.cols;
    printf("h=%d w=%d\n", height, width);
    cv::Mat gry_img(height, width, CV_8U);
    cv::Mat prc_img(height, width, CV_8U);

    cv::cvtColor(img, gry_img, cv::COLOR_BGR2GRAY);
    
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            prc_img.at<uchar>(y, x) = 255 - gry_img.at<uchar>(y, x);
        }
    }

    cv::imshow("img", img);
    cv::imshow("gry_img", gry_img);
    cv::imshow("prc_img", prc_img);
    
    cv::imwrite("dst_img.bmp", gry_img);

    cv::waitKey(0);

    return 0;
}
