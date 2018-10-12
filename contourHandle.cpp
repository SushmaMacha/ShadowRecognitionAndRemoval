/*
Authour - Sushma Macha
Finds the contours of a given picture and creates instantiations of functions in contourLeafs
to get the level and children information of the contours in the given picture
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "opencv2/opencv_modules.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "contourLeafs.cpp"

using namespace cv;
using namespace std;

int main()
{
	Mat image = imread("contours.jpg", cv::IMREAD_GRAYSCALE);

	Mat img;
	
	int i = 0,children = 0;

	//eliminate noise - select the kernel based on the noise
	GaussianBlur(image,img,Size(7,7),0,0);

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
	
	// Pre-requisite for findContours
	Canny(img,detected_edges,lower_threshold,lower_threshold*3,kernel_size);
	
	/* Finds the contours in the given picture and returns the vector of contours - 
	each contour vector consists of x,y coordinates all the points that belong to the contour
	Hierarchy - a vector that describes the hierarchy of contours
	[Next, prev, parent, First child] */
	findContours(detected_edges,contours,hierarchy,CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE);
	
	contourLeafs c(hierarchy);
	
	c.printHierarchy();
	
	while(i < contours.size())
	{
		cout << "Contour ID : " << i << endl; 
		/* Future use - to build a datastructure of contour id and children of the contour, 
		we need to just populate the structure with i and the return value of 
		the function findLevel in every iteration */
		cout << "Level : " << c.findLevel(i) << endl;
		c.findChildren(i,children);
		cout << "Children : "<< children << endl;
		// Reset the number of the children before every function call as the value is passed by address
		/* Future use - to build a datastructure of contour id and children of the contour, 
		we need to just populate the structure with i and children in every iteration */
		children = 0;
		i++;
	}
}
