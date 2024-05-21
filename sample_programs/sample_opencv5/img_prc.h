#ifndef _IMGPRC_H_
#define _IMGPRC_H_

#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#define MAX_BRIGHTNESS  255

class Img {
public:
    int width_L, height_L, width_R, height_R;
    cv::Mat imgL, imgR, dst_img;

    void determine_corresponding_point(int xL, int yL, int *xR, int *yR);
    void calc_range_data(int xL, int yL, int xR, int yR, double d, double f, double p_to_mm, double *xp, double *yp, double *zp);
    cv::Mat stereo_mathing();
};

#endif // _IMGPRC_H_