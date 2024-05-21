#include <iostream>
#include "img_prc.h"

int main(void)
{
    Img image;
    image.img = cv::imread("img07.bmp", 0);
    image.height = image.img.rows;
    image.width  = image.img.cols;
    printf("w=%d, h=%d\n", image.width, image.height);

    cv::imshow("src_img", image.img);

    image.prc_img = image.remove_areas();
    cv::imshow("prc_img", image.prc_img);

    cv::waitKey(0);
}