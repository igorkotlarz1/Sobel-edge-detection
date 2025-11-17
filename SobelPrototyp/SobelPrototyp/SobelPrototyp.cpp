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
	const char* inputFile = "Data/Images/cat.jpg";
	const char* grayFile = "Data/Images/cat_gray.jpg";
	const char* gaussFile = "Data/Images/cat_gauss.jpg";
	const char* sobelFile = "Data/Images/cat_sobel.jpg";
	const char* edgesFile = "Data/Images/cat_edges.jpg";
	std::string histFile = "Data/Histograms/histogram_cat.csv";

	int width,height,channels;
	BYTE* image = stbi_load(inputFile, &width, &height, &channels, 3);

	if (!image) {
		std::cout << "Failed to load image: " << stbi_failure_reason() << std::endl;
		return -1;
	}	

	//sequential version
	auto start = std::chrono::high_resolution_clock::now();

	std::vector<BYTE> grayImage = toGrayscale(image, width, height);

	auto end = std::chrono::high_resolution_clock::now();
	std::cout << "Elapsed time normal: " <<
		std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms.\n";

	//parallel version
	start = std::chrono::high_resolution_clock::now();
	int threads = std::thread::hardware_concurrency();

	std::vector<BYTE> grayImageParallel = toGrayscaleParallel(image, width, height, threads);

	end = std::chrono::high_resolution_clock::now();
	std::cout << "Elapsed time parallel: " << 
		std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms (" <<threads<<" threads)\n";

	/*std::vector<BYTE> gaussImage = applyGaussian(grayImage, width, height);
	std::vector<BYTE> sobelImage = calculateSobelMagnitude(gaussImage, width, height);
	detectEdges(sobelImage, width, height, 50);*/

	//stbi_write_jpg(edgesFile, width, height, 1, sobelImage.data(), 100);

	//intensity histogram
	//std::map<int, int> hist = getIntensityHist(grayImage, width, height);
	//toCSV(hist, histFile);

	stbi_image_free(image);
}
