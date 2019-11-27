#include "Strategy.h"
int g_no_of_learning_frames;

void Strategy::initializeForNewVideo(int rows, int cols)
{
	ASSERT(0, "initializeForNewVideo function should be called from derived classes");
}

void Strategy::initializeForNewImage()
{
	ASSERT(0, "initializeForNewImage function should be called from derived classes");
}

void Strategy::getSpecialPixelColor(float (&pc)[DIMENSION][DIMENSION], Pixel * p)
{}
void Strategy::getNormalPixelColor(float (&pc)[DIMENSION][DIMENSION], Pixel * p)
{}

void Strategy::setNewPixelColor(Pixel * p, int frameNo)
{
	ASSERT(0, "setNewPixelColor function should be called from derived classes");
}

void Strategy::endVideo()
{
	ASSERT(0, "endVideo function should be called from derived classes");
}

void Strategy::endImage()
{
	ASSERT(0, "endImage function should be called from derived classes");
}

void Strategy::getOrigColorFromPixel(Pixel * p, float & origColor)
{
	ASSERT(0, "getOrigColorFromPixel function should be called from derived classes");
}

void Strategy::getNewColorFromPixel(Pixel * p, float & newColor)
{
	ASSERT(0, "getNewColorFromPixel function should be called from derived classes");
}

void Strategy::setNewPixelColor(Pixel * p, const float & newColor)
{
	ASSERT(0, "setNewPixelColor function should be called from derived classes");
}

///////////////////////////////////////////////////////////////////////////////////////////////////

MOG::MOG()
{}

MOG::~MOG()
{}

void MOG::initializeForNewVideo(int rows, int cols)
{
	mog = (MixtureOfGuassian ***)malloc(rows * sizeof(MixtureOfGuassian **));
	for (int i = 0; i < rows; i++)
	{
		mog[i] = (MixtureOfGuassian **)malloc(cols * sizeof(MixtureOfGuassian *));
		for (int j = 0; j < cols; j++)
		{
			mog[i][j] = NULL;
		}
	}
}

void MOG::initializeForNewImage()
{}

void MOG::endImage()
{}

void MOG::endVideo()
{}

void MOG::setNewPixelColor(Pixel * p, int frameNo)
{
	float newPixelColor[DIMENSION][DIMENSION], currentPixelColor[DIMENSION][DIMENSION];
	int x, y;

	p->getOriginalColorValue(currentPixelColor);
	x = p->getX();
	y = p->getY();

	bool lBIsPixelPartOfForeground = false;

	MixtureOfGuassian * lTempMog = mog[x][y];
	if (lTempMog == NULL)
	{
		mog[x][y] = new MixtureOfGuassian();
		lTempMog = mog[x][y];
	}

	bool lBStartCalculatingSigma = false;
	if (frameNo >= g_no_of_learning_frames)
	{
		lBStartCalculatingSigma = true;
	}

	Guassian * lTempGuas = lTempMog->canPixelFitInAnyGuassian(currentPixelColor[0][0]);
	if (lTempGuas == NULL)
	{
		lTempMog->createNewGuassian(currentPixelColor[0][0], lBStartCalculatingSigma);
		lTempGuas = lTempMog->canPixelFitInAnyGuassian(currentPixelColor[0][0]);
		lBIsPixelPartOfForeground = lTempMog->gausPartOfForeground(lTempGuas);
	}
	else
	{
		lBIsPixelPartOfForeground = lTempMog->gausPartOfForeground(lTempGuas);
		lTempMog->updateGuassian(currentPixelColor[0][0], lTempGuas, lBStartCalculatingSigma);
	}

	if (lBIsPixelPartOfForeground)
	{
		getSpecialPixelColor(newPixelColor, p);
	}
	else
	{
		getNormalPixelColor(newPixelColor, p);
	}

	p->setNewColorValue(newPixelColor);
	p->setIsSpecialColored(lBIsPixelPartOfForeground);
}

void MOG::getOrigColorFromPixel(Pixel * p, float & origColor)
{
	float origColorTemp[DIMENSION][DIMENSION];
	p->getOriginalColorValue(origColorTemp);
	origColor = origColorTemp[0][0];
}

void MOG::getNewColorFromPixel(Pixel * p, float & newColor)
{
	float newColorTemp[DIMENSION][DIMENSION];
	p->getNewColorValue(newColorTemp);
	newColor = newColorTemp[0][0];
}

void MOG::setNewPixelColor(Pixel * p, const float & newColor)
{
	float newColorTemp[DIMENSION][DIMENSION];
	for (int i = 0; i < DIMENSION; i++)
	{
		newColorTemp[i][i] = newColor;
	}
	p->setNewColorValue(newColorTemp);
}

void MOG::getSpecialPixelColor(float (&pc)[DIMENSION][DIMENSION], Pixel * p)
{}
void MOG::getNormalPixelColor(float (&pc)[DIMENSION][DIMENSION], Pixel * p)
{}

void ForegroundSubtraction::getSpecialPixelColor(float (&pc)[DIMENSION][DIMENSION], Pixel * p)
{
	for (int i = 0; i < DIMENSION; i++)
	{
		for (int j = 0; j < DIMENSION; j++)
		{
			pc[i][j] = 0;
		}
		pc[i][0] = 105;
	}
}

void ForegroundSubtraction::getNormalPixelColor(float (&pc)[DIMENSION][DIMENSION], Pixel * p)
{
	float currentPixelColor[DIMENSION][DIMENSION];
	p->getOriginalColorValue(currentPixelColor);

	for (int i = 0; i < DIMENSION; i++)
	{
		for (int j = 0; j < DIMENSION; j++)
		{
			pc[i][j] = currentPixelColor[i][j];
		}
	}
}

void BackgroundSubtraction::getSpecialPixelColor(float (&pc)[DIMENSION][DIMENSION], Pixel * p)
{
	float currentPixelColor[DIMENSION][DIMENSION];
	p->getOriginalColorValue(currentPixelColor);

	for (int i = 0; i < DIMENSION; i++)
	{
		for (int j = 0; j < DIMENSION; j++)
		{
			pc[i][j] = 0;//currentPixelColor[i][j];
		}
		pc[i][0] = 255;
	}
}

void BackgroundSubtraction::getNormalPixelColor(float (&pc)[DIMENSION][DIMENSION], Pixel * p)
{
	for (int i = 0; i < DIMENSION; i++)
	{
		for (int j = 0; j < DIMENSION; j++)
		{
			pc[i][j] = 0;
		}
		pc[i][0] = 0;
	}
}