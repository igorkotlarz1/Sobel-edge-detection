#ifndef GAUSSIAN_H
#define GAUSSIAN_H
#endif 

#include "Utils.h"

std::vector<BYTE> applyGaussian(const std::vector<BYTE> &image, int width, int height);
std::vector<BYTE> applyGaussianParallel(const std::vector<BYTE>& image, int width, int height, int threadCount);
void applyGaussianPart(const std::vector<BYTE>& image, std::vector<BYTE>& resultImage, int width, int height, 
	int start, int end);