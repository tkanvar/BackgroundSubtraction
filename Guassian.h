#ifndef GUASSIAN_H
#define GUASSIAN_H

//#include "Utils.h"

using namespace std;

class Guassian
{
	float pi;
	float sigma;						// ASSUMPTION - VARIANCE OF RGB IS SAME
	float mu;							// ASSUMPTION - MEAN OF RGB IS SAME
	int noOfPixelsAdded;
	float probabilityLearningRate;
	float learningRate;

public:
	Guassian();
	~Guassian();

	void setPi(float p);
	float getPi();

	int getNoOfPixelsAdded();

	void setSigma(const float &s);
	void getSigma(float &result);
	bool calculateAndStoreSigma(const float &pixelColor);

	void setMu(const float &m);
	void getMu(float &result);
	bool calculateAndStoreMu(const float &pixelColor);

	void addedPixel();
	bool canPixelFitInGuassian(const float &pixelColor);

	void calculateProbabilityLearningRate(const float &pixelColor);
	void setLearningRate(float lr);

	void setProbabilityLearningRate(float plr);
};

#endif