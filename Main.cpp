#include "Utils.h"
#include "Video.h"
#include "Strategy.h"

float g_new_variance;
float g_back_threshold;
int g_no_of_gaussians;
int main(int argc, char** argv) 
{
	string srcVideoPath = argv[1];//"D:/WorkArea/IITD/MachineLearning/OpenCV/Gaussian/Gaussian/Video.mpg";
	string destVideoPath = argv[2];//"D:/WorkArea/IITD/MachineLearning/OpenCV/Gaussian/Gaussian/FrgndSubVideo.mpg";
	try
	{
		g_new_variance = stof(argv[3]);
		g_back_threshold = stof(argv[4]);
		g_no_of_learning_frames = stoi(argv[5]);
		g_no_of_gaussians = stoi(argv[6]);
	}
	catch(...)
	{
		cout << "Enter valid parameters\n";
		exit(0);
	}

	Video * v = new Video();
	//Strategy * s = new ForegroundSubtraction();
	Strategy * s = new BackgroundSubtraction();

	v->displayNewVideoUsingStrategy(s, srcVideoPath, destVideoPath);

    return 0;

}