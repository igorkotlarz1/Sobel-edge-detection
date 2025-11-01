#include "Gaussian.h"
#include <iostream>

int getIndexAt(int y, int x, int width)
{
	return y * width + x;
}

unsigned char* applyGaussian(unsigned char* image, int width, int height)
{
	unsigned char* gaussImage = new unsigned char[height * width];

	for (int i = 0; i < height; i++){
		for (int j = 0; j < width; j++){

			if (i == 0 || i == height || j == 0 || j == width) {
				gaussImage[getIndexAt(i, j, width)] = image[getIndexAt(i, j, width)];
				continue;
			}

			int sum = 0;
			sum += image[getIndexAt(i - 1, j - 1, width)];
			sum += image[getIndexAt(i - 1, j, width)] * 2;
			sum += image[getIndexAt(i - 1, j + 1, width)];

			sum += image[getIndexAt(i, j - 1, width)] * 2;
			sum += image[getIndexAt(i, j, width)] * 4;
			sum += image[getIndexAt(i, j + 1, width)] * 2;

			sum += image[getIndexAt(i + 1, j - 1, width)];
			sum += image[getIndexAt(i + 1, j, width)] * 2;
			sum += image[getIndexAt(i + 1, j + 1, width)];

			sum /= 16;
			gaussImage[getIndexAt(i, j, width)] = (unsigned char)sum;
		}
	}
	std::cout << "Applied Gaussian filter to the image" << std::endl;
	return gaussImage;
}
