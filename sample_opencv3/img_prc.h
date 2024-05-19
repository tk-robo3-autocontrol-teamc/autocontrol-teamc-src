#ifndef _IMGPRC_H_
#define _IMGPRC_H_

#include <stdio.h>
#include <opencv2/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>
#include <opencv2/imgproc/imgproc.hpp>

class Img {
public:
    int width, height;
    double div_const = 1.0;
    double pixel_value;
    double min, max;
    int thresh = 250;

    cv::Mat sobel(cv::Mat gry_img, int k);

    cv::Mat binarization(cv::Mat prc_img);
};

#endif // _IMGPRC_H_