#include <iostream>
#include <chrono>
#include <thread>
#include "Grayscale.h"
#include "Gaussian.h"

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "stb_image.h"
#include "stb_image_write.h"


int main()
{
	int width,height, channels;
	const char* inputFile = "Data/cat.jpg";
	const char* grayFile = "Data/cat_gray.jpg";
	const char* gaussFile = "Data/cat_gauss.jpg";

	unsigned char* image = stbi_load(inputFile, &width, &height, &channels, 3);

	if (!image) {
		std::cout << "Failed to load image: " << stbi_failure_reason() << std::endl;
		return -1;
	}	

	unsigned char* grayImage = toGrayscale(image, width, height);
	unsigned char* gaussImage = applyGaussian(image, width, height);

	//stbi_write_jpg(grayFile, width, height, 1, grayImage, 100);
	stbi_write_jpg(gaussFile, width, height, 1, gaussImage, 100);

	stbi_image_free(image);
	delete[] grayImage;
	delete[] gaussImage;
}
