#include "colour.h"
#include <iostream>

ColoredImage::ColoredImage(const std::string& imagePath) {
    image = cv::imread(imagePath);
    rows = image.rows;
    cols = image.cols;

    coloredImageVec.resize(rows, std::vector<std::vector<int>>(cols, std::vector<int>(3)));

    CopyImageToVector();
}
ColoredImage::~ColoredImage()
{
}
void ColoredImage::CopyImageToVector() {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            cv::Vec3b pixelValues = image.at<cv::Vec3b>(i, j);
            coloredImageVec[i][j][0] = static_cast<int>(pixelValues[0]); // Blue Channel
            coloredImageVec[i][j][1] = static_cast<int>(pixelValues[1]); // Green Channel
            coloredImageVec[i][j][2] = static_cast<int>(pixelValues[2]); // Red Channel
        }
    }
}
void ColoredImage::CopyVectorToMat() {
    processedImage = cv::Mat(rows, cols, CV_8UC3);

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            cv::Vec3b& pixelValues = processedImage.at<cv::Vec3b>(i, j);
            pixelValues[0] = static_cast<uchar>(coloredImageVec[i][j][0]); // Blue
            pixelValues[1] = static_cast<uchar>(coloredImageVec[i][j][1]); // Green
            pixelValues[2] = static_cast<uchar>(coloredImageVec[i][j][2]); // Red
        }
    }
}
void ColoredImage::ProcessImage() {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (coloredImageVec[i][j][1] > 50)
                coloredImageVec[i][j][1] -= 50;
        }
    }

    CopyVectorToMat();
}
void ColoredImage::ShowImages() const {
    cv::imshow("Original Image", image);
    cv::imshow("Processed Image", processedImage);
    cv::waitKey(0);
}

ColoredImage2::ColoredImage2(const std::string& imagePath) {
    image = cv::imread(imagePath);
    rows = image.rows;
    cols = image.cols;

    coloredImageVec.resize(rows * cols, std::vector<int>(3));

    CopyImageToVector();
}
ColoredImage2::~ColoredImage2() {
}
void ColoredImage2::CopyImageToVector() {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            cv::Vec3b pixelValues = image.at<cv::Vec3b>(i, j);
            int index = i * cols + j;
            coloredImageVec[index][0] = static_cast<int>(pixelValues[0]); // Blue Channel
            coloredImageVec[index][1] = static_cast<int>(pixelValues[1]); // Green Channel
            coloredImageVec[index][2] = static_cast<int>(pixelValues[2]); // Red Channel
        }
    }
}
void ColoredImage2::CopyVectorToMat() {
    processedImage = cv::Mat(rows, cols, CV_8UC3);

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            cv::Vec3b& pixelValues = processedImage.at<cv::Vec3b>(i, j);
            int index = i * cols + j;
            pixelValues[0] = static_cast<uchar>(coloredImageVec[index][0]); // Blue
            pixelValues[1] = static_cast<uchar>(coloredImageVec[index][1]); // Green
            pixelValues[2] = static_cast<uchar>(coloredImageVec[index][2]); // Red
        }
    }
}
void ColoredImage2::ProcessImage(int changered, int changegreen, int changeblue) {
    for (int i = 0; i < rows * cols; ++i) {
        coloredImageVec[i][0] += changeblue;
        coloredImageVec[i][1] -= changegreen;
        coloredImageVec[i][2] += changered;
    }

    CopyVectorToMat();
}
void ColoredImage2::ShowImages() const {
    cv::imshow("Original Image", image);
    cv::imshow("Processed Image", processedImage);
    cv::waitKey(0);
}

void cropImage(cv::Mat& image, const std::vector<int>& dim)
{
    int rows = image.rows;
    int cols = image.cols;

    if (dim.size() != 2 || dim[0] <= 0 || dim[1] <= 0 ||
        dim[0] > rows || dim[1] > cols)
    {
        std::cerr << "Invalid crop dimensions." << std::endl;
        return;
    }

    int sr = (rows - dim[0]) / 2;
    int sc = (cols - dim[1]) / 2;

    image = image(cv::Rect(sc, sr, dim[1], dim[0]));
}
void rotateImage(cv::Mat& image, const std::vector<int>& rpar)
{
    if (rpar.size() != 1 || (rpar[0] != 90 && rpar[0] != 180 && rpar[0] != 270))
    {
        std::cerr << "Invalid rotation degree. Valid options are 90, 180, or 270." << std::endl;
        return;
    }

    cv::Mat rmag;
    int rows = image.rows;
    int cols = image.cols;

    if (rpar[0] == 90)
    {
        rmag.create(cols, rows, image.type());
        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < cols; ++j)
            {
                rmag.at<cv::Vec3b>(j, rows - 1 - i) = image.at<cv::Vec3b>(i, j);
            }
        }
    }
    else if (rpar[0] == 180)
    {
        rmag.create(rows, cols, image.type());
        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < cols; ++j)
            {
                rmag.at<cv::Vec3b>(rows - 1 - i, cols - 1 - j) = image.at<cv::Vec3b>(i, j);
            }
        }
    }
    else if (rpar[0] == 270)
    {
        rmag.create(cols, rows, image.type());
        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < cols; ++j)
            {
                rmag.at<cv::Vec3b>(cols - 1 - j, i) = image.at<cv::Vec3b>(i, j);
            }
        }
    }

    image = rmag;
}
void quantizeChannels(cv::Mat& image, const std::vector<int>& lvl)
{
    if (lvl.size() != 3 || lvl[0] <= 0 || lvl[1] <= 0 || lvl[2] <= 0)
    {
        std::cerr << "Invalid level. Level must be greater than 0." << std::endl;
        return;
    }

    for (int i = 0; i < image.rows; i++)
    {
        for (int j = 0; j < image.cols; j++)
        {
            cv::Vec3b& pixelValues = image.at<cv::Vec3b>(i, j);
            pixelValues[0] = static_cast<uchar>(std::min(lvl[0], 128)); // Blue
            pixelValues[1] = static_cast<uchar>(std::min(lvl[1], 128)); // Green
            pixelValues[2] = static_cast<uchar>(std::min(lvl[2], 128)); // Red
        }
    }
}