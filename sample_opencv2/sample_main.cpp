#include <stdio.h>
#include <opencv2/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>
#include <opencv2/imgproc/imgproc.hpp>

int main(void)
{
    int width, height;
    double fps;
    cv::Mat frame;

    cv::VideoCapture capture(2);
    if (!capture.isOpened()) {
        return -1;
    }

    width = (int) capture.get(cv::CAP_PROP_FRAME_WIDTH);
    height = (int) capture.get(cv::CAP_PROP_FRAME_HEIGHT);
    fps = capture.get(cv::CAP_PROP_FPS);
    printf("image size %dx%d, %ffps\n", width, height, fps);

    char windowName[] = "web_camera";
    while (cv::waitKey(1) == -1) {
        capture >> frame;
        imshow(windowName, frame);
    }
    cv::destroyAllWindows();

    return 0;
}
