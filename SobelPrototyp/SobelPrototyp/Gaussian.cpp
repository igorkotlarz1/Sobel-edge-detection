#include "Gaussian.h"

std::vector<BYTE> applyGaussian(const std::vector<BYTE>& image, int width, int height)
{
	std::vector<BYTE> gaussImage(width * height);

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {

			if (i == 0 || i == height - 1 || j == 0 || j == width - 1) {
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
			gaussImage[getIndexAt(i, j, width)] = (BYTE) sum;
		}
	}
	std::cout << "Applied Gaussian filter to the image" << std::endl;
	return gaussImage;
}
