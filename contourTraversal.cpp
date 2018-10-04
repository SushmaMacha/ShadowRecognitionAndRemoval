#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "opencv2/opencv_modules.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "traversalModes.cpp"

using namespace cv;
using namespace std;

int main()
{
Mat image = imread("contour2.jpg", cv::IMREAD_GRAYSCALE);

Mat img;

//eliminate noise - select the kernel based on the noise
GaussianBlur(image,img,Size(11,11),0,0);

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

//print hierarchies - for debugging purposes
for (int i = 0;i < hierarchy.size();i++)
{
	cout << hierarchy[i][0] << " " << hierarchy[i][1] << " " << hierarchy[i][2] << " " <<  hierarchy[i][3] << endl;
}

int sz = contours.size();

//cout << "size : " << sz << endl;
//instantiate traversalModes to traverse the contour list
traversalModes TM(contours,hierarchy,sz);

TM.contourLevels();

TM.validateVisits();

TM.BFS();

}
