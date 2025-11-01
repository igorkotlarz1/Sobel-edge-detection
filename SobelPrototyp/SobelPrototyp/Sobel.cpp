#include "Sobel.h"
#include "Utils.h"
#include <cmath>

int* applySobelGX(unsigned char* image, int width, int height)
{
    int* outputImage = new int[height * width];

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {

            if (i == 0 || i == height - 1 || j == 0 || j == width - 1) {
                outputImage[getIndexAt(i, j, width)] = 0;
                continue;
            }
            //GX KERNEL
            //-1 0 1
            //-2 0 2
            //-1 0 1
            int sum = 0;
            sum += image[getIndexAt(i-1, j - 1, width)] * (-1);
            sum += image[getIndexAt(i-1, j, width)] * (-2);
            sum += image[getIndexAt(i-1, j + 1, width)] * (-1);

            sum += image[getIndexAt(i + 1, j - 1, width)];
            sum += image[getIndexAt(i + 1, j, width)] * 2;
            sum += image[getIndexAt(i + 1, j + 1, width)];

            outputImage[getIndexAt(i, j, width)] = sum;
        }
    }
    return outputImage;
}

int* applySobelGY(unsigned char* image, int width, int height)
{
    int* outputImage = new int[height * width];

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {

            if (i == 0 || i == height - 1 || j == 0 || j == width - 1) {
                outputImage[getIndexAt(i, j, width)] = 0;
                continue;
            }
            //GY KERNEL
            // 1  2  1
            // 0  0  0
            //-1 -2 -1            
             
            int sum = 0;
            sum += image[getIndexAt(i - 1, j - 1, width)];
            sum += image[getIndexAt(i, j - 1, width)] * 2;
            sum += image[getIndexAt(i + 1, j - 1, width)];

            sum += image[getIndexAt(i - 1, j + 1, width)] * (-1);
            sum += image[getIndexAt(i, j + 1, width)] * (-2);
            sum += image[getIndexAt(i + 1, j + 1, width)]* (-1);

            outputImage[getIndexAt(i, j, width)] = sum;
        }
    }
    return outputImage;
}

unsigned char* calculateSobelMagnitude(unsigned char* grayImage, int width, int height)
{
    int* sobelGX = applySobelGX(grayImage, width, height);
    int* sobelGY = applySobelGY(grayImage, width, height);

    unsigned char* outputImage = new unsigned char[width * height];

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            int sum = 0;
            
            sum += pow(sobelGX[getIndexAt(i, j, width)], 2)
                + pow(sobelGY[getIndexAt(i, j, width)], 2);
            outputImage[getIndexAt(i, j, width)] = (unsigned char)(sqrt(sum));
        }
    }
    std::cout << "Applied Sobel filters to the image" << std::endl;

    //freeing up alocated memory
    delete[] sobelGX;
    delete[] sobelGY;
    sobelGX = nullptr;
    sobelGY = nullptr;

    return outputImage;
}

void detectEdges(unsigned char* image, int width, int height, short threshold)
{
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {

            image[getIndexAt(i, j, width)] >= threshold ?
                image[getIndexAt(i, j, width)] = 255 : image[getIndexAt(i, j, width)] = 0;
        }
    }
    std::cout << "Applied binary thresholding to detect the edges with threshold value: " << threshold
        << std::endl;
}
