#ifndef _IMGPRC_H_
#define _IMGPRC_H_

#include <stdio.h>
#include <opencv2/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#define MAX_CNTR        5000
#define MAX_BRIGHTNESS  255
#define GRAY            128

class Img {
public:
    cv::Mat img, prc_img;
    int width, height;
    int chain_code[MAX_CNTR];
    int Freeman[8][2] = {
        {1, 0}, {1, -1}, {0, -1}, {-1, -1},
        {-1, 0}, {-1, 1}, {0, 1}, {1, 1}
    };

    int obtain_contour(int x_start, int y_start);
    cv::Mat remove_areas();
};

#endif // _IMGPRC_H_