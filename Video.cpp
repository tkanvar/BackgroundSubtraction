#include "Video.h"

Video::Video()
{
	workingOnFrameNoMutex = 0;
}

Video::~Video()
{}

void Video::setVideoPath(string vp)
{
	VideoCapture cap(vp);
	currentVideo = cap;

	if (!cap.isOpened())
    {
        ASSERT(0, "!!! Failed to open file: " + vp);
        return;
    }
}
bool Video::getNextImageFromVideo(Mat & currentFrameData)
{
	if (!currentVideo.read(currentFrameData))             
	{
		return false;
	}

	if (COLOR_DECODING == 1)
	{
		cvtColor(currentFrameData, currentFrameData, COLOR_BGR2GRAY);
	}

	return true;
}

void Video::displayNewVideoUsingStrategy(Strategy * s, string videoPathName, string destVideoPathName)
{
	setVideoPath(videoPathName);

	int frame_width = currentVideo.get(CV_CAP_PROP_FRAME_WIDTH); 
	int frame_height = currentVideo.get(CV_CAP_PROP_FRAME_HEIGHT); 
	int frameRate = currentVideo.get(CAP_PROP_FPS);
	int fcc1 = CV_FOURCC('P','I','M','1');
	VideoWriter destCap(destVideoPathName, fcc1, currentVideo.get(CAP_PROP_FPS), Size(frame_width,frame_height), (COLOR_DECODING == 0) ? true : false);

	Mat currentFrameData;
	bool lBHasNextImage = getNextImageFromVideo(currentFrameData);

	s->initializeForNewVideo(currentFrameData.rows, currentFrameData.cols);

	int totalNoOfFrames = 100;//currentVideo.get(CAP_PROP_FRAME_COUNT);

	vector<thread *> prepareConnectedComponent;

	int i = 0;
	while(lBHasNextImage)
	{
		cout << "Frame " << i+1 << "\n";

		Image * currentFrame = new Image(i);

		currentFrame->prepareNewImageUsingStrategy(s, currentFrameData, i);

		thread * t = new thread(&Video::prepareConnectedComponentInImage, this, s, currentFrame, i, destCap);
		prepareConnectedComponent.push_back(t);

		lBHasNextImage = getNextImageFromVideo(currentFrameData);

		i++;
	}

	for (auto& t : prepareConnectedComponent)
	{
		t->join();
	}

	for (auto& t : prepareConnectedComponent)
	{
		delete t;
		t = 0;
	}

	s->endVideo();
}

void Video::prepareConnectedComponentInImage(Strategy * s, Image * currentFrame, int frameNo, VideoWriter & destCap)						// THREAD
{
	Mat newImageData;
	currentFrame->displayNewImageUsingStrategy(s, newImageData);

	// Synchronous flow of threads
	while(workingOnFrameNoMutex != frameNo)
	{}

	destCap.write(newImageData);

	workingOnFrameNoMutex++;

	delete currentFrame;
	currentFrame = 0;
}