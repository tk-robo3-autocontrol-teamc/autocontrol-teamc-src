#include <stdio.h>
#include <opencv2/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>
#include <opencv2/imgproc/imgproc.hpp>

int main(void)
{
    cv::Mat img;
    cv::Mat gry_img, sblx_img, sbly_img, sblxy_img, cvt_img, thld_img;
    int thresh = 100;

    img = cv::imread("img_211208_3.bmp", 1);

    cv::cvtColor(img, gry_img, cv::COLOR_BGR2GRAY);
    cv::Sobel(gry_img, sblx_img, CV_32F, 1, 0, 3);
    cv::Sobel(gry_img, sbly_img, CV_32F, 0, 1, 3);
    sblxy_img = abs(sblx_img) + abs(sbly_img);
    cv::convertScaleAbs(sblxy_img, cvt_img, 1, 0);
    cv::threshold(cvt_img, thld_img, thresh, 255, cv::THRESH_BINARY);

    cv::imshow("img", img);
    cv::imshow("sblxy_img", sblxy_img);
    cv::imshow("cvt_img", cvt_img);
    cv::imshow("dist_img.bmp", thld_img);

    cv::waitKey(0);

    return 0;
}
