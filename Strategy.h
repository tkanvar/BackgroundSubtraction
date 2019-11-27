#ifndef STRATEGY_H
#define STRATEGY_H

#include "Utils.h"
#include "MixtureOfGuassian.h"
#include "Pixel.h"

class Strategy
{
public:
	virtual void initializeForNewVideo(int rows, int cols);
	virtual void initializeForNewImage();
	virtual void endVideo();
	virtual void endImage();
	virtual void setNewPixelColor(Pixel * p, int frameNo);
	virtual void getOrigColorFromPixel(Pixel * p, float & origColor);
	virtual void getNewColorFromPixel(Pixel * p, float & newColor);
	virtual void setNewPixelColor(Pixel * p, const float & newColor);
	virtual void getSpecialPixelColor(float (&pc)[DIMENSION][DIMENSION], Pixel * p);
	virtual void getNormalPixelColor(float (&pc)[DIMENSION][DIMENSION], Pixel * p);
};

class MOG : public Strategy
{
	MixtureOfGuassian *** mog;

public:
	MOG();
	~MOG();

	void initializeForNewVideo(int rows, int cols);
	void initializeForNewImage();
	void endVideo();
	void endImage();
	void setNewPixelColor(Pixel * p, int frameNo);
	void getOrigColorFromPixel(Pixel * p, float & origColor);
	void getNewColorFromPixel(Pixel * p, float & newColor);
	void setNewPixelColor(Pixel * p, const float & newColor);
	virtual void getSpecialPixelColor(float (&pc)[DIMENSION][DIMENSION], Pixel * p);
	virtual void getNormalPixelColor(float (&pc)[DIMENSION][DIMENSION], Pixel * p);
};

class ForegroundSubtraction: public MOG
{
public:
	void getSpecialPixelColor(float (&pc)[DIMENSION][DIMENSION], Pixel * p);
	void getNormalPixelColor(float (&pc)[DIMENSION][DIMENSION], Pixel * p);
};

class BackgroundSubtraction: public MOG
{
public:
	void getSpecialPixelColor(float (&pc)[DIMENSION][DIMENSION], Pixel * p);
	void getNormalPixelColor(float (&pc)[DIMENSION][DIMENSION], Pixel * p);
};

#endif