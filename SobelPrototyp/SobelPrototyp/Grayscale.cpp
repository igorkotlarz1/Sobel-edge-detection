#include "Grayscale.h"

std::vector<BYTE> toGrayscale(BYTE* image, int width, int height)
{
	int size = width * height * 3;
	int j = 0;
	std::vector<BYTE> resultImage(width * height);

	for (int i = 0; i < size; i += 3)
	{
		BYTE red = image[i];
		BYTE green = image[i + 1];
		BYTE blue = image[i + 2];

		BYTE gray = (BYTE)(0.299 * red + 0.587 * green + 0.114 * blue);

		resultImage[j] = gray;
		j++;
	}
	std::cout << "Converted image to grayscale." << std::endl;

	return resultImage;
}
