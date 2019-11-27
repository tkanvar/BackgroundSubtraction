#ifndef PIXEL_H
#define PIXEL_H

#include "Utils.h"

class Pixel
{
	int x;
	int y;
	float originalColorValue[DIMENSION][DIMENSION];
	float newColorValue[DIMENSION][DIMENSION];
	bool isSpecialColored;

	Pixel * nextPixel;

public:
	void setX(int px);
	void setY(int py);

	int getX();
	int getY();

	void setOriginalColorValue(const float (&originalColorValue)[DIMENSION][DIMENSION]);
	void setNewColorValue(const float (&newColorValue)[DIMENSION][DIMENSION]);

	void getOriginalColorValue(float (&originalColorValue)[DIMENSION][DIMENSION]);
	void getNewColorValue(float (&newColorValue)[DIMENSION][DIMENSION]);

	void setIsSpecialColored(bool isclrd);
	bool getIsSpecialColored();

	void setNextPixel(Pixel * nextP);
	Pixel * getNextPixel();

	void copyOrigColorToNewColor();
};

#endif