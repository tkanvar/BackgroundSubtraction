#include "Guassian.h"
#include "Utils.h"

using namespace std;

Guassian::Guassian()
{

	sigma = g_new_variance;
	mu = 0;
	pi = 1;
	noOfPixelsAdded = 0;
}

Guassian::~Guassian()
{}

void Guassian::setPi(float p)
{
	pi = p;
}
float Guassian::getPi()
{
	return pi;
}

void Guassian::setSigma(const float &s)
{
	sigma = s;
}
void Guassian::getSigma(float &result)
{
	result = sigma;
}
bool Guassian::calculateAndStoreSigma(const float &pixelColor)
{
	if (noOfPixelsAdded == 0)						// New guassian
	{
		sigma = g_new_variance;
	}
	else												// Fit point in existing guassian
	{
		float intermSigma1 = (1 - probabilityLearningRate) * sigma;
		float intermSigma2 = probabilityLearningRate * pow((pixelColor - mu), 2);
		sigma = intermSigma1 + intermSigma2;
	}

	return true;
}

void Guassian::setMu(const float &m)
{
	mu = m;
}
void Guassian::getMu(float &result)
{
	result = mu;
}
bool Guassian::calculateAndStoreMu(const float &pixelColor)
{
	if (noOfPixelsAdded == 0)												// New Guassian
	{
		mu = pixelColor;
	}
	else																			// Existing Guassian
	{
		float intermMu1 = (1 - probabilityLearningRate) * mu;
		float intermMu2 = probabilityLearningRate * pixelColor;
		mu = intermMu1 + intermMu2;
	}

	return true;
}

void Guassian::calculateProbabilityLearningRate(const float &pixelColor)
{
	float denominator = 1 / (pow((2.0 * 22.0 * sigma / 7.0), 0.5));
	float exponentTerm = -1 * pow((pixelColor - mu), 2) / (2 * sigma);
	float neta = denominator * exp(exponentTerm);

	probabilityLearningRate = learningRate * neta;
}

void Guassian::setProbabilityLearningRate(float plr)
{
	probabilityLearningRate = plr;
}

void Guassian::setLearningRate(float lr)
{
	learningRate = lr;
}

void Guassian::addedPixel()
{
	noOfPixelsAdded++;
}
int Guassian::getNoOfPixelsAdded()
{
	return noOfPixelsAdded;
}

bool Guassian::canPixelFitInGuassian(const float &pixelColor)
{
	float dist = pixelColor - mu;
	if (dist < -2.5 * sqrt(sigma) || dist > 2.5 * sqrt(sigma))
	{
		return false;
	}

	return true;
}