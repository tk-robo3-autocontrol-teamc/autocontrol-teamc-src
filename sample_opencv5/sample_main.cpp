#include <iostream>
#include "img_prc.h"

int main(void)
{
    Img image;

    image.imgL = cv::imread("img_L.bmp", 1);
    image.imgR = cv::imread("img_R.bmp", 1);

    image.width_L = image.imgL.cols;
    image.height_L = image.imgL.rows;
    image.width_R = image.imgR.cols;
    image.height_R = image.imgR.rows;
    printf("Left image size %dx%d\n", image.width_L, image.height_L);
    printf("Right image size %dx%d\n", image.width_R, image.height_R);

    cv::Mat gry_imgL(image.width_L, image.height_L, CV_8U);
    cv::Mat gry_imgR(image.width_R, image.height_R, CV_8U);

    cv::cvtColor(image.imgL, gry_imgL, cv::COLOR_BGR2GRAY);
    cv::cvtColor(image.imgR, gry_imgR, cv::COLOR_BGR2GRAY);
    image.imgL = gry_imgL;
    image.imgR = gry_imgR;

    image.dst_img = image.stereo_mathing();

    cv::imshow("img_L", image.imgL);
    cv::imshow("img_R", image.imgR);
    cv::imshow("stereo_img", image.dst_img);

    cv::waitKey(0);
    cv::destroyAllWindows();

    return 0;
}