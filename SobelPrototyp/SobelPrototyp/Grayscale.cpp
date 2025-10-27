#include "Grayscale.h"
#include <iostream>

unsigned char* toGrayscale(unsigned char* image, int width, int height)
{
	int size = width * height * 3;
	int j = 0;
	unsigned char* resultImage = new unsigned char[width * height];

	for (int i = 0; i < size; i += 3)
	{
		
		unsigned char red = image[i];
		unsigned char green = image[i+1];
		unsigned char blue = image[i+2];

		unsigned char gray = (unsigned char)(0.299 * red + 0.587 * green + 0.114 * blue);

		resultImage[j] = gray;
		j++;
	}
	std::cout << "Converted image to grayscale." << std::endl;

	return resultImage;

}
