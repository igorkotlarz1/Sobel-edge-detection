#ifndef GRAYSCALE_H
#define GRAYSCALE_H
#endif 

#include "Utils.h"
std::vector<BYTE> toGrayscale(BYTE* image, int width, int height);
std::vector<BYTE> toGrayscaleParallel(BYTE* image, int width, int height, int threadCount);
void toGrayScalePart(BYTE* image, std::vector<BYTE>& resultImage, int start, int end);