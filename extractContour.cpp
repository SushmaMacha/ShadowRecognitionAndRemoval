#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "opencv2/opencv_modules.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc.hpp"
//#include "traversalModes.cpp"

using namespace cv;
using namespace std;

#define debug 0

int main()
{
Mat image = imread("contour2.jpg", cv::IMREAD_GRAYSCALE);

Mat img;

//eliminate noise - select the kernel based on the noise
GaussianBlur(image,img,Size(7,7),0,0);

Mat detected_edges;

//variables for canny
int lower_threshold = 50;
int kernel_size = 3;

//variables for contours
vector <vector<Point>> contours;
//No of points in which a given contour can fit into a polygon
vector<Point> approx;
vector <Vec4i> hierarchy;

//variables for drawContours
Mat mask(360, 480, CV_8UC1,255);

//Output image
Mat output(360, 480, CV_8UC1,255);

//colored contours
Scalar colorF(30,120,30);

Canny(img,detected_edges,lower_threshold,lower_threshold*3,kernel_size);

findContours(detected_edges,contours,hierarchy,CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE);

int sz = contours.size();

#if debug
for (int i = 0;i < hierarchy.size();i++)
{
	cout << "Contour : "<< i << "   " << hierarchy[i][0] << " " << hierarchy[i][1] << " " << hierarchy[i][2] << " " <<  hierarchy[i][3] << endl;
}
#endif

for(int j=0;j<sz;j++)
{
	int circle = -1;
	double area = -1,peri=-1;
	approxPolyDP(contours[j],approx,2,true);
	area = contourArea(contours[j]);
	peri = arcLength(contours[j],false);
	if(approx.size()>7 && area < 1300 && peri < 250)
	{
		circle = j;
		#if debug
			cout << "Contour : "<< circle << " length : " <<approx.size() << " area : " << area << " peri : "<<peri<<endl;
		#endif
	}
	if(circle != -1)
	{
		drawContours(mask,contours,circle,Scalar(0,0,0),-1,8,hierarchy,0,Point());
	}
}
namedWindow("Mask", WINDOW_AUTOSIZE);
imshow("Mask",mask);
while(1)
{
	char k = waitKey(33);
	if(k == 27)
		break;
}

bitwise_and(img,mask,img);
namedWindow("Input", WINDOW_AUTOSIZE);
imshow("Input",image);
while(1)
{
	char k = waitKey(33);
	if(k == 27)
		break;
}
namedWindow("Output", WINDOW_AUTOSIZE);
imshow("Output",img);
while(1)
{
	char k = waitKey(33);
	if(k == 27)
		break;
}
}

