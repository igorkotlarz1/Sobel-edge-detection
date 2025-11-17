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

std::vector<BYTE> calculatelMagnitude(const std::vector<BYTE>& image, int width, int height)
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

    //std::cout << "Applied binary thresholding to detect the edges with threshold value: " << threshold << std::endl;
}

void sobelGXPart(const std::vector<BYTE>& image, std::vector<BYTE>& resultImage, int width, int height, int start, int end)
{
    for (int i = start; i < end; i++) {
        for (int j = 0; j < width; j++) {

            if (i == 0 || i == height - 1 || j == 0 || j == width - 1) {
                resultImage[getIndexAt(i, j, width)] = 0;
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

            resultImage[getIndexAt(i, j, width)] = sum;
        }
    }
}

void sobelGYPart(const std::vector<BYTE>& image, std::vector<BYTE>& resultImage, int width, int height, int start, int end)
{
    for (int i = start; i < end; i++) {
        for (int j = 0; j < width; j++) {

            if (i == 0 || i == height - 1 || j == 0 || j == width - 1) {
                resultImage[getIndexAt(i, j, width)] = 0;
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

            resultImage[getIndexAt(i, j, width)] = sum;
        }
    }
}

std::vector<int> sobelGXParallel(const std::vector<BYTE>& image, int width, int height, int threadCount)
{
    int rows = height / threadCount;

    std::vector<int> resultImage(width * height);
    std::vector<std::thread> threads;

    for (int i = 0; i < threadCount; i++) {

        int start = i * rows;
        int end;

        if (i == threadCount - 1)
            end = height;
        else
            end = start + rows;

        threads.emplace_back(sobelGXPart, std::cref(image),std::ref(resultImage),width, height, start, end);
    }

    for (auto& thread : threads)
        thread.join();

    return resultImage;
}

std::vector<int> sobelGYParallel(const std::vector<BYTE>& image, int width, int height, int threadCount)
{
    int rows = height / threadCount;

    std::vector<int> resultImage(width * height);
    std::vector<std::thread> threads;

    for (int i = 0; i < threadCount; i++) {

        int start = i * rows;
        int end;

        if (i == threadCount - 1)
            end = height;
        else
            end = start + rows;

        threads.emplace_back(sobelGYPart, std::cref(image), std::ref(resultImage), width, height, start, end);
    }

    for (auto& thread : threads)
        thread.join();

    return resultImage;
}

void calculateMagnitudePart(const std::vector<BYTE>& image, const std::vector<int>& GX, const std::vector<int>& GY, 
    std::vector<BYTE>& resultImage, int width, int height, int start, int end)
{
    for (int i = start; i < end; i++) {

        int sum = 0;
        int gx_sqrd = GX[i] * GX[i];
        int gy_sqrd = GY[i] * GY[i];

        sum += gx_sqrd + gy_sqrd;
        resultImage[i] = (unsigned char)(sqrt(sum));
    }
}

std::vector<BYTE> calculateMagnitudeParallel(const std::vector<BYTE>& image, int width, int height, int threadCount)
{
    int size = width * height;
    int chunkSize = size / threadCount;

    std::vector<int> gx = sobelGXParallel(image, width, height, threadCount);
    std::vector<int> gy = sobelGYParallel(image, width, height, threadCount);

    std::vector<BYTE> resultImage(size);
    std::vector<std::thread> threads;

    for (int i = 0; i < threadCount; i++) {

        int start = i * chunkSize;
        int end;

        if (i == threadCount - 1)
            end = size;
        else
            end = start + chunkSize;

        threads.emplace_back(calculateMagnitudePart, std::cref(gx), std::cref(gy), std::ref(resultImage),
            width, height, start, end);
    }
   
    for (auto& thread : threads)
        thread.join();

    return resultImage;
}


