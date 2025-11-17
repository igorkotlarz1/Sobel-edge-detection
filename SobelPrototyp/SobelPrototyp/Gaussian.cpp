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

	return gaussImage;
}

std::vector<BYTE> applyGaussianParallel(const std::vector<BYTE>& image, int width, int height, int threadCount)
{
	int size = width * height;
	int chunkSize = size / threadCount;

	std::vector<BYTE> resultImage(size);
	std::vector<std::thread> threads;

	for (int i = 0; i < threadCount; i++) {

		int start = i * chunkSize;
		int end;

		if (i == threadCount - 1)
			end = size;
		else
			end = start + chunkSize;

		threads.emplace_back(applyGaussianPart, std::cref(image), std::ref(resultImage), width, height, start, end);
	}

	for (auto& thread : threads)
		thread.join();

	return resultImage;
}

void applyGaussianPart(const std::vector<BYTE>& image, std::vector<BYTE>& resultImage, int width, int height, int start, int end) 
{

	for (int i = start; i < end; i++) {
		for (int j = 0; j < width; j++) {

			if (i == 0 || i == height - 1 || j == 0 || j == width - 1) {
				resultImage[getIndexAt(i, j, width)] = image[getIndexAt(i, j, width)];
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
			resultImage[getIndexAt(i, j, width)] = (BYTE)sum;
		}
	}
}
