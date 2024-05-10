#pragma once

#ifndef GRAYSCALE_IMAGE_PROCESSOR_H
#define GRAYSCALE_IMAGE_PROCESSOR_H

#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>

void g1(cv::Mat& image);
void g2(cv::Mat& image, int intensityChange);
void cropImage3(cv::Mat& image, const std::vector<int>& cropDimensions);
void rotateImage3(cv::Mat& image, int degreeOfRotation);
void quantizeChannels(cv::Mat& image, int level);

#endif 