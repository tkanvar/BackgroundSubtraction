#ifndef UTILS_H
#define UTILS_H

#include <map>
#include <vector>
#include <iostream>
#include <cv.h>
#include <highgui.h>
#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <opencv2/core/core_c.h>
#include <thread>

#define snprintf _sprintf

using namespace std;
using namespace cv;

extern float g_new_variance;
extern float g_back_threshold;
extern int g_no_of_learning_frames;
extern int g_no_of_gaussians;

#define DIMENSION 3						// RGB - 3, GreyScale - 1
//#define NEW_VARIANCE 400					// For new guassian, the new variance will be
//#define NO_OF_GAUSSIANS 5				// Threshold of gaussians considered as background
//#define THRESHOLD 0.8					// Threshold of gaussians considered as background
#define COLOR_DECODING 0				// 0 - BGR, 1 - GreyScale
//#define NO_OF_LEARNING_FRAMES 25

enum typeOfSubtarction
{
	foreground,
	background
};

#define MESSAGE(errorMsg) \
{ \
	cout << "WARNING:\n" << __FILE__ << ":" << __LINE__ << "\n"; \
	cout << errorMsg << "\n"; \
}

#define ASSERT(condition, errorMsg) \
{ \
	if (!condition) \
	{\
		cout << "ERROR\n" << __FILE__ << ":" << __LINE__ << "\n"; \
		cout << errorMsg << "\n"; \
	}\
}

#endif