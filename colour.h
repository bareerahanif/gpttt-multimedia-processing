#pragma once
#ifndef COLORED_IMAGE_H
#define COLORED_IMAGE_H

#include <opencv2/opencv.hpp>
#include <vector>

class ColoredImage 
{
public:
    ColoredImage(const std::string& imagePath);
    ~ColoredImage();

    void ProcessImage();

    void ShowImages() const;

private:
    std::vector<std::vector<std::vector<int>>> coloredImageVec;
    int rows, cols;

    cv::Mat image;
    cv::Mat processedImage;

    void CopyImageToVector();
    void CopyVectorToMat();
};
class ColoredImage2
{
public:
    ColoredImage2(const std::string& imagePath);
    ~ColoredImage2();

    void ProcessImage(int changered, int changegreen, int changeblue);

    void ShowImages() const;

private:
    std::vector<std::vector<int>> coloredImageVec;
    int rows, cols;

    cv::Mat image;
    cv::Mat processedImage;

    void CopyImageToVector();
    void CopyVectorToMat();
};

void cropImage(cv::Mat& image, const std::vector<int>& cropDimensions);
void rotateImage(cv::Mat& image, const std::vector<int>& rotationParams);
void quantizeChannels(cv::Mat& image, const std::vector<int>& channelLevels);

#endif