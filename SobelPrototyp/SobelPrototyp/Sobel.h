#ifndef SOBEL_H
#define SOBEL_H

int* applySobelGX(unsigned char* image, int width, int height);
int* applySobelGY(unsigned char* image, int width, int height);
unsigned char* calculateSobelMagnitude(unsigned char* grayImage, int width, int height);
void detectEdges(unsigned char* image, int width, int height, short threshold);

#endif // !SOBEL_H

