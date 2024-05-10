#include <opencv2/opencv.hpp>
#include <iostream>

void tc(int, void*);

int blueIncrement{};
int greenIncrement{};
int redIncrement{};

int main()
{
    cv::VideoCapture cap(0);

    cv::Mat img;

    cv::namedWindow("Web Cam", cv::WINDOW_NORMAL);

    cv::createTrackbar("Blue", "Web Cam", &blueIncrement, 255, tc, &img);
    cv::createTrackbar("Green", "Web Cam", &greenIncrement, 255, tc, &img);
    cv::createTrackbar("Red", "Web Cam", &redIncrement, 255, tc, &img);

    while (1)
    {
        cap.read(img);
        char key = cv::waitKey(10);

        if (key == 27)
            break;

        tc(0, &img);  
        cv::imshow("Web Cam", img);
    }

    cap.release();
    cv::destroyAllWindows();
    return 0;
}

void tc(int, void* userdata)
{
    cv::Mat* img = static_cast<cv::Mat*>(userdata);

    for (int y = 0; y < img->rows; ++y) {
        for (int x = 0; x < img->cols; ++x) {
            img->at<cv::Vec3b>(y, x)[0] = cv::saturate_cast<uchar>(img->at<cv::Vec3b>(y, x)[0] + blueIncrement);
            img->at<cv::Vec3b>(y, x)[1] = cv::saturate_cast<uchar>(img->at<cv::Vec3b>(y, x)[1] + greenIncrement);
            img->at<cv::Vec3b>(y, x)[2] = cv::saturate_cast<uchar>(img->at<cv::Vec3b>(y, x)[2] + redIncrement);
        }
    }

    cv::imshow("Web Cam", *img);
}
