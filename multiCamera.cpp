/*Author : Sushma, Student ID: 011548719.
Program : Multithreading application to process videos from multiple cameras simultaneously.
Creates two threads, each of which can perform Gaussian Blur, Histogram Equalization on each frame.
*/

#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include <mutex>
#include "opencv2/opencv_modules.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc.hpp"

using namespace std; 
using namespace cv;

void camera1(VideoCapture &cap1, string windowName);

void camera1(VideoCapture &cap1, string windowName)
{
	mutex mu;
	if(!cap1.isOpened())
	{
		cout <<"could not open"<<endl;
	}
	
	while(1)
	{
		Mat frame1,blurFrm1,src,dest;
		cap1 >> frame1;
		//process till the last frame
		if(frame1.empty())
		break;
		//GaussianBlur to reduce noise
		GaussianBlur(frame1,blurFrm1,Size(7,7),0);
		cvtColor(blurFrm1,src,CV_BGR2GRAY);
		//Histogram Equalization to distribute the intensity of pixels equally
		equalizeHist(src,dest);
		//Display the results
		imshow(windowName,dest);
		char c1 = (char)waitKey(20);
		//close the window when 'ESC' is pressed
		if(c1 == 27)
		break;
	}
}


int main(int argc, char **argv)
{
	string img_path1 = "IMG_3153.MOV";
	string img_path2 = "IMG_3322.MOV";
	VideoCapture cap1(img_path1);
	VideoCapture cap2(img_path2);
	void (*cam) (VideoCapture &cap1, string windowName);
	cam = camera1;
	//create windows to display the results
	namedWindow("cam1", CV_WINDOW_AUTOSIZE);
	namedWindow("cam2", CV_WINDOW_AUTOSIZE);
	//create threads to process the video clips from camera1,camera2
	thread t1 (cam,std::ref(cap1),"cam1");
	thread t2 (cam,std::ref(cap2),"cam2");
	//wait till both the threads complete processing video clips
	t1.join();
	t2.join();
	return 0;
}
