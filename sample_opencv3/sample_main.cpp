#include <iostream>
#include "img_prc.h"

int main(void)
{
    Img image;

    cv::Mat img;

    img = cv::imread("img_211208_3.bmp", 1);
    image.height = img.rows;
    image.width  = img.cols;
    printf("h=%d w=%d\n", image.height, image.width);

    cv::Mat gry_img(image.height, image.width, CV_8U);
    cv::Mat prc_img(image.height, image.width, CV_8U);
    cv::Mat prc_img_1(image.height, image.width, CV_8U);
    cv::Mat prc_img_2(image.height, image.width, CV_8U);
    cv::Mat dst_img(image.height, image.width, CV_8U);

    cv::cvtColor(img, gry_img, cv::COLOR_BGR2GRAY);

    prc_img_1 = image.sobel(gry_img, 0);
    prc_img_2 = image.sobel(gry_img, 1);

    prc_img = prc_img_1 + prc_img_2;
    dst_img = image.binarization(prc_img);

    cv::imshow("img", img);
    cv::imshow("gry_img", gry_img);
    cv::imshow("prc_img", prc_img);
    cv::imshow("prc_img_1", prc_img_1);
    cv::imshow("prc_img_2", prc_img_2);
    cv::imshow("dst_img", dst_img);

    cv::imwrite("img_tst.bmp", dst_img);

    cv::waitKey(0);

    return 0;
}