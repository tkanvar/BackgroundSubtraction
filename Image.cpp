#include "Image.h"

Image::Image(int cfn)
{
	currentFrameNo = cfn;
	rowCntr = 0;
	colCntr = -1;
	newPixelColors.clear();
}

Image::~Image()
{
	for (int i = 0; i < listOfPixels.size(); i++)
	{
		delete listOfPixels[i];
		listOfPixels[i] = 0;
	}
	listOfPixels.clear();
}

void Image::setImageData(Mat id)
{
	imageData = id;
}

bool Image::getNextPixelFromImage(float (&currentPixelData)[DIMENSION][DIMENSION])
{
	colCntr++;
	if (colCntr >= imageData.cols)
	{
		rowCntr++;
		if (rowCntr < imageData.rows)
		{
			colCntr = 0;
		}
		else
		{
			return false;
		}
	}

	memset(currentPixelData, 0, DIMENSION*DIMENSION*sizeof(float));

	if (DIMENSION == 1)
	{
		uchar p = imageData.at<uchar>(rowCntr, colCntr);
		float ip = (float) p;
		currentPixelData[0][0] = ip;
	}
	else if (DIMENSION == 3)
	{
		Point3_<uchar>* p = imageData.ptr<Point3_<uchar> >(rowCntr, colCntr);
		float ip1 = (float)(p->x);			// B
		float ip2 = (float)(p->y);			// G
		float ip3 = (float)(p->z);			// R
		currentPixelData[0][0] = ip1;
		currentPixelData[1][0] = ip2;
		currentPixelData[2][0] = ip3;
	}

	return true;
}

void Image::prepareNewImageUsingStrategy(Strategy * s, const Mat & imageData, int frameNo)
{
	setImageData(imageData);
	s->initializeForNewImage();

	float currentPixelColor[DIMENSION][DIMENSION];
	while(getNextPixelFromImage(currentPixelColor))
	{
		Pixel * p = new Pixel();
		p->setX(rowCntr);
		p->setY(colCntr);
		p->setOriginalColorValue(currentPixelColor);

		listOfPixels.push_back(p);
	}

	for (int i = 0; i < listOfPixels.size(); i++)
	{
		s->setNewPixelColor(listOfPixels[i], frameNo);
	}
}

void Image::displayNewImageUsingStrategy(Strategy * s, Mat & returnImageData)					// Part of Thread
{
	float pixelColor[DIMENSION][DIMENSION];
	for (int i = 0; i < listOfPixels.size(); i++)
	{	
		listOfPixels[i]->getNewColorValue(pixelColor);
		pushInOpenCVImage(pixelColor, (i == listOfPixels.size()-1) ? true : false);
	}

	s->endImage();
	returnImageData = newImageData;
}

void Image::pushInOpenCVImage(const float (&newPixelColor)[DIMENSION][DIMENSION], bool pBIsLast)
{
	if (DIMENSION == 1)
	{
		newPixelColors.push_back(newPixelColor[0][0]);
	}
	else if (DIMENSION == 3)
	{
		newPixelColors.push_back(newPixelColor[0][0]);
		newPixelColors.push_back(newPixelColor[1][0]);
		newPixelColors.push_back(newPixelColor[2][0]);
	}
	
	if (pBIsLast)
	{
		uchar * newPixelColorsArray = (uchar *)malloc(newPixelColors.size());
		for (int i = 0; i < newPixelColors.size(); i++)
		{
			newPixelColorsArray[i] = newPixelColors[i];
		}
		newImageData = imageData.clone();
		newImageData = Mat(imageData.rows, imageData.cols, CV_8UC(DIMENSION), newPixelColorsArray);
	}
}