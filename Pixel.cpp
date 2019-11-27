#include "Pixel.h"

void Pixel::setX(int px)
{
	x = px;
}
void Pixel::setY(int py)
{
	y = py;
}
int Pixel::getX()
{
	return x;
}
int Pixel::getY()
{
	return y;
}

void Pixel::copyOrigColorToNewColor()
{
	float origColor[DIMENSION][DIMENSION];
	getOriginalColorValue(origColor);
	setNewColorValue(origColor);
}

void Pixel::setOriginalColorValue(const float (&ocv)[DIMENSION][DIMENSION])
{
	memcpy(originalColorValue, ocv, DIMENSION*DIMENSION*sizeof(float));
}
void Pixel::setNewColorValue(const float (&ncv)[DIMENSION][DIMENSION])
{
	memcpy(newColorValue, ncv, DIMENSION*DIMENSION*sizeof(float));
}
void Pixel::getNewColorValue(float (&ncv)[DIMENSION][DIMENSION])
{
	memcpy(ncv, newColorValue, DIMENSION*DIMENSION*sizeof(float));
}
void Pixel::getOriginalColorValue(float (&ocv)[DIMENSION][DIMENSION])
{
	memcpy(ocv, originalColorValue, DIMENSION*DIMENSION*sizeof(float));
}

void Pixel::setIsSpecialColored(bool isclrd)
{
	isSpecialColored = isclrd;
}
bool Pixel::getIsSpecialColored()
{
	return isSpecialColored;
}

void Pixel::setNextPixel(Pixel * p)
{
	nextPixel = p;
}
Pixel * Pixel::getNextPixel()
{
	return nextPixel;
}