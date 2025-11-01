#ifndef HISTOGRAM_H
#define HISTOGRAM_H

#include <map>
#include <string>
using namespace std;

map<int, int> getIntensityHist(unsigned char* image, int width, int height);
void toCSV(map<int, int>& intensityDict, const string& filePath);

#endif // !HISTOGRAM_H

