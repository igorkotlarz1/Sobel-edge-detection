#include <iostream>
#include <chrono>
#include <thread>

#include "Histogram.h"
#include "Grayscale.h"
#include "Gaussian.h"
#include "Sobel.h"

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "stb_image.h"
#include "stb_image_write.h"


int main()
{
	int width,height, channels;
	const char* inputFile = "Data/Images/cat.jpg";
	//const char* grayFile = "Data/Images/cat_gray.jpg";
	//const char* gaussFile = "Data/Images/cat_gauss.jpg";
	const char* sobelFile = "Data/Images/cat_sobel.jpg";
	const char* edgesFile = "Data/Images/cat_edges.jpg";

	unsigned char* image = stbi_load(inputFile, &width, &height, &channels, 3);

	if (!image) {
		std::cout << "Failed to load image: " << stbi_failure_reason() << std::endl;
		return -1;
	}	

	unsigned char* grayImage = toGrayscale(image, width, height);
	//unsigned char* gaussImage = applyGaussian(grayImage, width, height);
	//unsigned char* sobelImage = calculateSobelMagnitude(gaussImage, width, height);

	map<int, int> hist = getIntensityHist(grayImage, width, height);
	toCSV(hist, "Data/Histograms/histogram_cat.csv");

	//stbi_write_jpg(sobelFile, width, height, 1, sobelImage, 100);

	//detectEdges(sobelImage, width, height, 50);

	//stbi_write_jpg(edgesFile, width, height, 1, sobelImage, 100);

	stbi_image_free(image);
	delete[] grayImage;
	//delete[] gaussImage;
	//delete[] sobelImage;


}
