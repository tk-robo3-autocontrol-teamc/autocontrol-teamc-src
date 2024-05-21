#include <iostream>
#include "img_prc.h"

int Img::obtain_contour(int x_start, int y_start)
{
    int x, y;
    int xs, ys;
    int code, num;
    int i, counter, detect;

    counter = 0;
    for (i = 0; i < 8; i++) {
        xs = x_start + Freeman[i][0];
        ys = y_start + Freeman[i][1];

        if (xs >= 0 && xs <= width &&
            ys >= 0 && ys <= height &&
            img.at<uchar>(ys, xs) == 255) {
            counter++;
        }
    }

    if (counter == 0) {
        num = 1;
    } else {
        num = -1;
        x = x_start;
        y = y_start;
        code = 0;

        do {
            detect = 0;
            code = code - 3;
            if (code < 0) code = code + 8;

            do {
                xs = x + Freeman[code][0];
                ys = y + Freeman[code][1];

                if (xs >= 0 && xs <= width &&
                    ys >= 0 && ys <= height &&
                    img.at<uchar>(ys, xs) == 255) {
                    detect = 1;
                    num++;
                    if (num > MAX_CNTR) {
                        printf("%d\n", MAX_CNTR);
                        exit(1);
                    }
                    chain_code[num] = code;
                    x = xs;
                    y = ys;
                }
                code++;
                if (code > 7) {
                    code = 0;
                }
            } while (detect == 0);
        } while (x != x_start || y != y_start);
        num = num + 2;
    }
    return num;
}

cv::Mat Img::remove_areas()
{
    int threshold;
    int num, x, y, xs, ys, i;
    int fill_value;
    cv::Mat tmp_img(height, width, CV_8U);

    std::cout << "Input max pixel of contour: " << std::endl;
    std::cin >> threshold;

    for (y = 0; y < height; y++) {
        for (x = 0; x < width; x++) {
            if (img.at<uchar>(y, x) == 255) {
                num = obtain_contour(x, y);
                if (num > threshold) {
                    fill_value = 255;
                } else {
                    fill_value = GRAY;
                }

                xs = x;
                ys = y;
                img.at<uchar>(ys, xs) = 0;
                tmp_img.at<uchar>(ys, xs) = (unsigned char) fill_value;

                if (num > 1) {
                    for (i = 0; i < num-1; i++) {
                        xs = xs + Freeman[chain_code[i]][0];
                        ys = ys + Freeman[chain_code[i]][1];
                        img.at<uchar>(ys, xs) = 0;
                        tmp_img.at<uchar>(ys, xs) = (unsigned char) fill_value;
                    }
                }
            }
        }
    }

    for (y = 0; y < height; y++) {
        for (x = 0; x < width; x++) {
            if (img.at<uchar>(y, x) == GRAY) {
                tmp_img.at<uchar>(y, x) = 0;
                for (i = 0; i < 8; i++) {
                    xs = x + Freeman[i][0];
                    ys = y + Freeman[i][1];
                    if (xs >= 0 && xs <= width &&
                        ys >= 0 && ys <= height &&
                        img.at<uchar>(ys, xs) == 255) {
                        tmp_img.at<uchar>(y, x) = 255;
                    }
                }
            }
        }
    }

    return tmp_img;
}
