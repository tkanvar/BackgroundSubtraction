#ifndef IMAGE_H
#define IMAGE_H

#include "Utils.h"
#include "Strategy.h"
#include "Pixel.h"

class Image
{
	Mat imageData, newImageData;
	vector<uchar> newPixelColors;
	int rowCntr, colCntr;
	vector<Pixel *> listOfPixels;
	int currentFrameNo;

public:
	Image(int cfn);
	~Image();

	void setImageData(Mat id);
	bool getNextPixelFromImage(float (&currentPixelData)[DIMENSION][DIMENSION]);
	void prepareNewImageUsingStrategy(Strategy * s, const Mat & imageData, int frameNo);
	void displayNewImageUsingStrategy(Strategy * s, Mat & returnImageData);
	void pushInOpenCVImage(const float (&newPixelColor)[DIMENSION][DIMENSION], bool pBIsLast);
};

#endif