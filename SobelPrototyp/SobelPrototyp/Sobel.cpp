#include "Sobel.h"
#include <cmath>

std::vector<int> applySobelGX(const std::vector<BYTE>& image, int width, int height)
{
    std::vector<int> outputImage(height*width);

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
            sum += image[getIndexAt(i - 1, j - 1, width)] * (-1);
            sum += image[getIndexAt(i - 1, j, width)] * (-2);
            sum += image[getIndexAt(i - 1, j + 1, width)] * (-1);

            sum += image[getIndexAt(i + 1, j - 1, width)];
            sum += image[getIndexAt(i + 1, j, width)] * 2;
            sum += image[getIndexAt(i + 1, j + 1, width)];

            outputImage[getIndexAt(i, j, width)] = sum;
        }
    }
    return outputImage;
}

std::vector<int> applySobelGY(const std::vector<BYTE>& image, int width, int height)
{
    std::vector<int> outputImage(height * width);

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
            sum += image[getIndexAt(i + 1, j + 1, width)] * (-1);

            outputImage[getIndexAt(i, j, width)] = sum;
        }
    }
    return outputImage;
}

std::vector<BYTE> calculateSobelMagnitude(const std::vector<BYTE>& image, int width, int height)
{
    std::vector<int> sobelGX = applySobelGX(image, width, height);
    std::vector<int> sobelGY = applySobelGY(image, width, height);

    std::vector<BYTE> outputImage(height * width);

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            int sum = 0;

            sum += pow(sobelGX[getIndexAt(i, j, width)], 2)
                + pow(sobelGY[getIndexAt(i, j, width)], 2);
            outputImage[getIndexAt(i, j, width)] = (unsigned char)(sqrt(sum));
        }
    }
    std::cout << "Applied Sobel filters to the image" << std::endl;

    return outputImage;
}

void detectEdges(std::vector<BYTE>& image, int width, int height, short threshold)
{
    int size = width * height;
    
    for(int i = 0; i < size; i++) {
        //image[i] >= threshold ?
         //   image[i] = 255 : image[i] = 0;
		image[i] = (image[i] >= threshold) ? 255 : 0;
	}

    std::cout << "Applied binary thresholding to detect the edges with threshold value: " << threshold
		<< std::endl;
}


