
#include "grayscale.h"
#include <iostream>

void g1(cv::Mat& image)
{
    int rows = image.rows;
    int cols = image.cols;

    std::vector<std::vector<int>> imageArr(rows, std::vector<int>(cols, 0));

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            imageArr[i][j] = static_cast<int>(image.at<uchar>(i, j));
        }
    }

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (imageArr[i][j] > 50)
                imageArr[i][j] -= 50;
        }
    }

    cv::imshow("Grayscale Image", image);
}
void g2(cv::Mat& image, int intensityChange)
{
    int rows = image.rows;
    int cols = image.cols;

    std::vector<std::vector<int>> grayarr(rows * cols, std::vector<int>(1, 0));

    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            uchar pixelValue = image.at<uchar>(i, j);
            int index = i * cols + j;
            grayarr[index][0] = static_cast<int>(pixelValue);
        }
    }

    std::cout << "Do you want to increase or decrease the intensity? (Enter '1' for increase, '-1' for decrease, '0' for no change): ";
    int choice;
    std::cin >> choice;

    if (choice == 1)
    {
        std::cout << "Enter value to increase intensity: ";
    }
    else if (choice == -1)
    {
        std::cout << "Enter value to decrease intensity: ";
    }
    else
    {
        intensityChange = 0;
    }

    std::cin >> intensityChange;

    for (int i = 0; i < rows * cols; ++i)
    {
        grayarr[i][0] += choice * intensityChange;
        grayarr[i][0] = std::max(0, std::min(255, grayarr[i][0]));
    }

    cv::Mat processedImage(rows, cols, CV_8UC1);

    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            uchar& pixelValue = processedImage.at<uchar>(i, j);
            int index = i * cols + j;
            pixelValue = static_cast<uchar>(grayarr[index][0]);
        }
    }

    cv::imshow("Original Image", image);
    cv::imshow("Processed Image", processedImage);

    cv::waitKey(0);
}
void cropImage3(cv::Mat& image, const std::vector<int>& cropDimensions)
{
    int rows = image.rows;
    int cols = image.cols;

    if (cropDimensions.size() != 2 || cropDimensions[0] <= 0 || cropDimensions[1] <= 0 ||
        cropDimensions[0] > rows || cropDimensions[1] > cols)
    {
        std::cerr << "Invalid crop dimensions." << std::endl;
        return;
    }

    int startRow = (rows - cropDimensions[0]) / 2;
    int startCol = (cols - cropDimensions[1]) / 2;

    image = image(cv::Rect(startCol, startRow, cropDimensions[1], cropDimensions[0]));
}
void rotateImage3(cv::Mat& image, int degreeOfRotation)
{
    if (degreeOfRotation != 90 && degreeOfRotation != 180 && degreeOfRotation != 270)
    {
        std::cerr << "Invalid rotation degree. Valid options are 90, 180, or 270." << std::endl;
        return;
    }

    cv::Mat rotatedImage;
    int rows = image.rows;
    int cols = image.cols;

    if (degreeOfRotation == 90)
    {
        rotatedImage.create(cols, rows, image.type());
        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < cols; ++j)
            {
                rotatedImage.at<uchar>(j, rows - 1 - i) = image.at<uchar>(i, j);
            }
        }
    }
    else if (degreeOfRotation == 180)
    {
        rotatedImage.create(rows, cols, image.type());
        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < cols; ++j)
            {
                rotatedImage.at<uchar>(rows - 1 - i, cols - 1 - j) = image.at<uchar>(i, j);
            }
        }
    }
    else if (degreeOfRotation == 270)
    {
        rotatedImage.create(cols, rows, image.type());
        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < cols; ++j)
            {
                rotatedImage.at<uchar>(cols - 1 - j, i) = image.at<uchar>(i, j);
            }
        }
    }

    image = rotatedImage;
}
void quantizeChannels(cv::Mat& image, int level)
{
    if (level <= 0)
    {
        std::cerr << "Invalid level. Level must be greater than 0." << std::endl;
        return;
    }

    level = std::min(level, 128);

    for (int i = 0; i < image.rows; i++)
    {
        for (int j = 0; j < image.cols; j++)
        {
            uchar& pixelValue = image.at<uchar>(i, j);
            pixelValue = static_cast<uchar>(level);
        }
    }
}