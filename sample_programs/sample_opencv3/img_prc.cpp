#include <iostream>
#include "img_prc.h"

cv::Mat Img::sobel(cv::Mat gry_img, int k)
{
    int weight[2][3][3] = {
        {
            {-1,  0,  1},
            {-2,  0,  2},
            {-1,  0,  1}
        },
        {
            {-1, -2, -1},
            { 0,  0,  0},
            { 1,  2,  1}
        }
    };

    cv::Mat tmp_img(height, width, CV_8U);

    min = (double) INT_MAX;
    max = (double) INT_MIN;

    for (int y = 1; y < height-1; y++) {
        for (int x = 1; x < width-1; x++) {
            pixel_value = 0.0;
            for (int i = -1; i < 2; i++) {
                for (int j = -1; j < 2; j++) {
                    pixel_value = pixel_value + weight[k][i+1][j+1] * gry_img.at<uchar>(y+i, x+j);
                }
            }

            pixel_value = pixel_value / div_const;
            if (pixel_value < min) min = pixel_value;
            if (pixel_value > max) max = pixel_value;
        }
    }

    for (int y = 1; y < height-1; y++) {
        for (int x = 1; x < width-1; x++) {
            pixel_value = 0.0;
            for (int i = -1; i < 2; i++) {
                for (int j = -1; j < 2; j++) {
                    pixel_value = pixel_value + weight[k][i+1][j+1] * gry_img.at<uchar>(y+i, x+j);
                }
            }

            pixel_value = pixel_value /div_const;
            pixel_value = 255 / (max - min) * (pixel_value - min);
            tmp_img.at<uchar>(y, x) = (unsigned char) pixel_value;
        }
    }

    return tmp_img;
}

cv::Mat Img::binarization(cv::Mat prc_img)
{
    cv::Mat tmp_img(height, width, CV_8U);

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (prc_img.at<uchar>(y, x) < thresh) {
                tmp_img.at<uchar>(y, x) = 255;
            } else {
                tmp_img.at<uchar>(y, x) = 0;
            }
        }
    }

    return tmp_img;
}
