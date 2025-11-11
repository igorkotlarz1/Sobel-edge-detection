#ifndef SOBEL_H
#define SOBEL_H
#endif 

#include "Utils.h"

std::vector<int> applySobelGX(const std::vector<BYTE>& image, int width, int height);
std::vector<int> applySobelGY(const std::vector<BYTE>& image, int width, int height);
std::vector<BYTE> calculateSobelMagnitude(const std::vector<BYTE>& image, int width, int height);
void detectEdges(std::vector<BYTE>& image, int width, int height, short threshold);



