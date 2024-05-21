#include <iostream>
#include "img_prc.h"

void Img::determine_corresponding_point(int xL, int yL, int *xR, int *yR)
{
    cv::Mat tmp_img(100, 100, CV_8U);

    int x_tmp = 5;
    int y_tmp = 3;
    int x_offset = 128;

    int out_flag;
    int threshold_for_gray = 20;
    int y_offset = 1;

    int i, j, m, n, xp, yp, xs, ys;
    int num_of_temp = 0;
    double sum, min_error;
    double error_ratio;
    double min_gray, max_gray;

    num_of_temp = 0;
    min_gray = 255.0;
    max_gray = 0.0;

    out_flag = 0;
    for (i = -y_tmp; i <= y_tmp; i++) {
        for (j = -x_tmp; j <= x_tmp; j++) {
            xp = xL + j;
            yp = yL + i;

            if (xp < 0 || xp > width_L || yp < 0 || yp > height_L) {
                out_flag = 1;
            } else {
                num_of_temp++;
                tmp_img.at<uchar>(i+y_tmp, j+x_tmp) = imgL.at<uchar>(yp, xp);

                if (imgL.at<uchar>(yp, xp) < min_gray) {
                    min_gray = imgL.at<uchar>(yp, xp);
                } else if (imgL.at<uchar>(yp, xp) > max_gray) {
                    max_gray = imgL.at<uchar>(yp, xp);
                }
            }
        }
    }
    if ((max_gray - min_gray) <= threshold_for_gray || out_flag == 1) {
        *xR = xL - 1;
        *yR = yL;
    } else {
        min_error = 10000.0;
        for (m = -y_offset; m <= y_offset; m++) {
            for (n = -x_offset; n < 0; n++) {
                xs = xL + n;
                ys = yL + m;
                if (xs >= 0 && xs < width_L && ys >= 0 && ys < height_L) {
                    sum = 0.0;
                    for (i = -y_tmp; i <= y_tmp; i++) {
                        for (j = -x_tmp; j <= x_tmp; j++) {
                            xp = xs + j;
                            yp = ys + i;
                            if (xp >= 0 && xp < width_L && yp >= 0 && yp < height_L) {
                                sum = sum + abs(tmp_img.at<uchar>(i+y_tmp, j+x_tmp) - imgR.at<uchar>(yp, xp));
                            }
                        }
                    }
                    error_ratio = sum / num_of_temp;
                    if (error_ratio <= min_error) {
                        min_error = error_ratio;
                        *xR = xs;
                        *yR = ys;
                    }
                }
            }
        }
    }
}

void Img::calc_range_data(int xL, int yL, int xR, int yR, double d, double f, double p_to_mm, double *xp, double *yp, double *zp)
{
    double disparity;

    xL = xL - (int) (width_L / 2.0);
    yL = -(yL - (int) (height_L / 2.0));
    xR = xR - (int) (width_L / 2.0);
    yR = -(yR - (int) (height_L / 2.0));

    disparity = (xL - xR) * p_to_mm;
    *xp = d * xL / disparity;
    *yp = d * yL / disparity;
    *zp = f * d / disparity;
}

cv::Mat Img::stereo_mathing()
{
    double d = 60.0;
    double f = 3.6;
    double pixel_to_mm = 0.08;

    int min_range = 100;
    int max_range = 600;
    int xL, yL, xR, yR;
    double xp, yp, zp;
    int min_dist, max_dist;

    cv::Mat range(height_L, width_L, CV_8U);
    cv::Mat dst_img(height_L, width_L, CV_8U);

    for (yL = 0; yL < height_L; yL++) {
        for (xL = 0; xL < width_L; xL++) {
            range.at<uchar>(yL, xL) = 0;
        }
    }
    
    printf("Base image: Left\n");
    for (yL = 0; yL < height_L; yL++) {
        for (xL = 0; xL < width_L; xL++) {
            determine_corresponding_point(xL, yL, &xR, &yR);
            calc_range_data(xL, yL, xR, yR, d, f, pixel_to_mm, &xp, &yp, &zp);
            range.at<uchar>(yL, xL) = (int) zp;
        }
    }

    for (yL = 0; yL < height_L; yL++) {
        for (xL = 0; xL < width_L; xL++) {
            if (range.at<uchar>(yL, xL) <= min_range) {
                range.at<uchar>(yL, xL) = min_range;
            }
            if (range.at<uchar>(yL, xL) > max_range) {
                range.at<uchar>(yL, xL) = max_range;
            }
        }
    }

    min_dist = INT_MAX;
    max_dist = INT_MIN;
    for (yL = 0; yL < height_L; yL++) {
        for (xL = 0; xL < width_L; xL++) {
            if (range.at<uchar>(yL, xL) < min_dist) {
                min_dist = range.at<uchar>(yL, xL);
            } else if (range.at<uchar>(yL, xL) > max_dist) {
                max_dist = range.at<uchar>(yL, xL);
            }
        }
    }

    for (yL = 0; yL < height_L; yL++) {
        for (xL = 0; xL < width_L; xL++) {
            dst_img.at<uchar>(yL, xL) = (unsigned char) (MAX_BRIGHTNESS - MAX_BRIGHTNESS * (range.at<uchar>(yL, xL) - min_dist) / (double) (max_dist - min_dist));
        }
    }

    return dst_img;
}
