#include <iostream>
#include <chrono>
#include <thread>
#include "Grayscale.h"

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "stb_image.h"
#include "stb_image_write.h"


int main()
{
	int width,height, channels;
	const char* inputFile = "Data/cat.jpg";
	const char* outputFile = "Data/cat_gray.jpg";

	unsigned char* image = stbi_load(inputFile, &width, &height, &channels, 3);

	if (!image) {
		std::cout << "Failed to load image: " << stbi_failure_reason() << std::endl;
		return -1;
	}	

	unsigned char* grayImage = toGrayscale(image, width, height);

	stbi_write_jpg(outputFile, width, height, 1, grayImage, 100);

	stbi_image_free(image);
	delete[] grayImage;
}
