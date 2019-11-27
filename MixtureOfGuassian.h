#ifndef MIXTURE_OF_GUASSIAN_H
#define MIXTURE_OF_GUASSIAN_H

#include "Utils.h"
#include "Guassian.h"

class MixtureOfGuassian
{
	float learningRate;
	vector<Guassian *> listOfGuassians;

private:
	void rearrangeGuassians();
	void recalculatePiOfAllGuassians(int currentGuassianPos);
	void calculateLearningRate();
	int getGuassianPos(Guassian * g);

public:
	MixtureOfGuassian();
	~MixtureOfGuassian();

	int getNoOfGuassians();
	Guassian * canPixelFitInAnyGuassian(const float &pixelColor);
	void createNewGuassian(const float &pixelColor, bool pBStartCalcSigma);
	void updateGuassian(const float &pixelColor, Guassian * g, bool pBStartCalcSigma);
	bool gausPartOfForeground(Guassian * g);
};

#endif