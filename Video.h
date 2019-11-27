#ifndef VIDEO_H
#define VIDEO_H

#include "Utils.h"
#include "Image.h"
#include "Strategy.h"

class Video
{
	VideoCapture currentVideo;
	int workingOnFrameNoMutex;

	void prepareConnectedComponentInImage(Strategy * s, Image * currentFrame, int frameNo, VideoWriter & destCap);

public:
	Video();
	~Video();

	void setVideoPath(string videoPath);
	bool getNextImageFromVideo(Mat & currentFrameData);
	void displayNewVideoUsingStrategy(Strategy * s, string videoPathName, string destVideoPathName);
};

#endif