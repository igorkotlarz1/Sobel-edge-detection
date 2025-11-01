#include "Histogram.h"
#include <fstream>
#include <iostream>

map<int, int> getIntensityHist(unsigned char* image, int width, int height)
{
	int size = height * width;

	map<int, int> intensityDict;

	for (int i = 0; i < size; i++) {
		int brightness = (int)image[i];
		intensityDict[brightness]++;
	}

	return intensityDict;
}

void toCSV(map<int, int>& intensityDict, const string& filePath)
{
	ofstream file(filePath);
	int range = 255;

	for (int i = 0; i <= 255; i++)
		file << i << "," << intensityDict[i] << "\n";

	file.close();
	cout << "Saved hist data to " << filePath << endl;
	
}
