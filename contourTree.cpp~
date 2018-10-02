#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "opencv2/opencv_modules.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "stackContours.cpp"

using namespace cv;
using namespace std;

int main()
{
Mat image = imread("contour.jpg", cv::IMREAD_GRAYSCALE);

Mat img;

//define levels at which the contours need to be highlighted
int level1 = 2,level2 = 3;

//eliminate noise - select the kernel based on the noise
GaussianBlur(image,img,Size(3,3),0,0);

Mat detected_edges;

//variables for canny
int lower_threshold = 50;
int kernel_size = 3;

//variables for contours
vector <vector<Point>> contours;
vector <Vec4i> hierarchy;

//variables for drawContours
Mat canvas(650, 1160, CV_8UC3,Scalar(0,0,0));

//colored contours
Scalar colorF(30,120,30);

Canny(img,detected_edges,lower_threshold,lower_threshold*3,kernel_size);

findContours(detected_edges,contours,hierarchy,CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE);

//instantiate a stack with the number of contours
Stack s(contours.size());

// Draw contours
int i = 0,j = 0;

//Level at which you need a color change
int level=0;


while(1)
{
	//Create a window to display contours
	namedWindow("contours", WINDOW_AUTOSIZE);
	imshow("contours",canvas);
	while(1)
	{
		char k = waitKey(33);
		if(k==27)
		break;
	}
	//Hierarchy array - [Next,Previous,FirstChild,Parent]
	//Check for a child
	if(hierarchy[i][2] != -1)
	{
		//push parent
		s.push(i);level++;
		//point to child
		i = hierarchy[i][2];
		cout << i <<"level :"<<level<< endl;
		if(level == level1 || level == level2)
			drawContours(canvas,contours,i,colorF,2,8,hierarchy,0,Point());
		else
			drawContours(canvas,contours,i,Scalar(255),2,8,hierarchy,0,Point());
		continue;
	}
	//If no children, check for next contour
	else if(hierarchy[i][0] != -1)
	{
		//point to next
		i = hierarchy[i][0];
		cout << i << endl;
		if(level == level1 || level == level2)
			drawContours(canvas,contours,i,colorF,2,8,hierarchy,0,Point());
		else
			drawContours(canvas,contours,i,Scalar(255),2,8,hierarchy,0,Point());
		continue;
	}
	//if neither break
	else
	{
		if(s.empty||(i==contours.size()-1))
		{
			break;		
		}
		while(1)
		{
			
			i = s.pop();level--;	
			cout << i <<"level :"<<level<< endl;
			if(level == level1 || level == level2)
				drawContours(canvas,contours,i,colorF,2,8,hierarchy,0,Point());
			else
				drawContours(canvas,contours,i,Scalar(255),2,8,hierarchy,0,Point());
			if(hierarchy[i][0] != -1)
			{
				//point to next
				i = hierarchy[i][0];
				cout << i << endl;
				if(level == 5)
					drawContours(canvas,contours,i,colorF,2,8,hierarchy,0,Point());
				else
					drawContours(canvas,contours,i,Scalar(255),2,8,hierarchy,0,Point());
				break;
			}
			if(s.empty||i==(contours.size()-1))
				break;
		}
	}

}
}

