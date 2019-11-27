#include "MixtureOfGuassian.h"

MixtureOfGuassian::MixtureOfGuassian()
{
	listOfGuassians.clear();
	learningRate = 1.0;
}

MixtureOfGuassian::~MixtureOfGuassian()
{
}

int MixtureOfGuassian::getNoOfGuassians()
{
	return listOfGuassians.size();
}

Guassian * MixtureOfGuassian::canPixelFitInAnyGuassian(const float &pixelColor)
{
	for (int i = 0; i < listOfGuassians.size(); i++)
	{
		if (listOfGuassians[i]->canPixelFitInGuassian(pixelColor))
		{
			return listOfGuassians[i];
		}
	}

	return NULL;
}

void MixtureOfGuassian::createNewGuassian(const float &pixelColor, bool pBStartCalcSigma)
{
	Guassian * g = new Guassian();
	listOfGuassians.push_back(g);

	g->setLearningRate(learningRate);
	g->setProbabilityLearningRate(learningRate);
	g->calculateAndStoreMu(pixelColor);
	if (pBStartCalcSigma)
	{
			g->calculateAndStoreSigma(pixelColor);
	}
	g->addedPixel();
	calculateLearningRate();	
	recalculatePiOfAllGuassians(listOfGuassians.size()-1);

	rearrangeGuassians();
}

void MixtureOfGuassian::updateGuassian(const float &pixelColor, Guassian * g, bool pBStartCalcSigma)
{
	g->setLearningRate(learningRate);
	g->calculateProbabilityLearningRate(pixelColor);
	g->calculateAndStoreMu(pixelColor);
	if (pBStartCalcSigma)
	{
			g->calculateAndStoreSigma(pixelColor);
	}
	g->addedPixel();
	calculateLearningRate();
	recalculatePiOfAllGuassians(getGuassianPos(g));

	rearrangeGuassians();
}

void MixtureOfGuassian::calculateLearningRate()
{
	int totalEle = 0;
	for (int i = 0; i < listOfGuassians.size(); i++)
	{
		if (listOfGuassians[i]->getNoOfPixelsAdded() == 0)
		{
			cout << "No of pixels added in a gaussian cannot be zero\n";
			exit(0);
		}
		totalEle += listOfGuassians[i]->getNoOfPixelsAdded();
	}

	learningRate = (float)1 / (float)(totalEle == 0 ? 1 : totalEle);
}

void MixtureOfGuassian::rearrangeGuassians()
{
	float lTempSigma;
	for (int i = 1; i < listOfGuassians.size(); i++)
	{
		listOfGuassians[i]->getSigma(lTempSigma);
		float ith_Heuristic = listOfGuassians[i]->getPi() / lTempSigma;

		int j;
		for (j = i-1; j >= 0; j--)
		{
			float jth_Heuristic = listOfGuassians[j]->getPi() / (sqrt(lTempSigma));
			if (jth_Heuristic >= ith_Heuristic)
			{
				break;
			}
		}
		j++;

		Guassian * lIthGuas = listOfGuassians[j];
		for (int k = j; k < i; k++)
		{
			listOfGuassians[k] = listOfGuassians[k+1];
		}
		listOfGuassians[i] = lIthGuas;
	}

	if (g_no_of_gaussians < listOfGuassians.size())
	{
		for (int i = g_no_of_gaussians+1; i < listOfGuassians.size(); i++)
		{
			delete listOfGuassians[i];
			listOfGuassians[i] = 0;
			listOfGuassians.erase(listOfGuassians.begin()+i);
			i--;
		}
	}
}

int MixtureOfGuassian::getGuassianPos(Guassian * g)
{
	for (int i = 0; i < listOfGuassians.size(); i++)
	{
		if (listOfGuassians[i] == g)
		{
			return i;
		}
	}

	return -1;
}

void MixtureOfGuassian::recalculatePiOfAllGuassians(int currentGuassianPos)
{
	for (int i = 0; i < listOfGuassians.size(); i++)
	{
		float pi = (1.0 - (float)learningRate) * listOfGuassians[i]->getPi() + learningRate * (currentGuassianPos == i ? 1.0 : 0.0);
		listOfGuassians[i]->setPi(pi);
	}
}

bool MixtureOfGuassian::gausPartOfForeground(Guassian * g)
{
	bool lBIsGaussianFound = false;
	float backgroundPi = 0;

	for (int i = 0; i < listOfGuassians.size(); i++)
	{
		if (listOfGuassians[i] == g)
		{
			lBIsGaussianFound = true;
		}

		backgroundPi += listOfGuassians[i]->getPi();
		if (backgroundPi > g_back_threshold)
		{
			break;
		}
	}

	return !lBIsGaussianFound;
}