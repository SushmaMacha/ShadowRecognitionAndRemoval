#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "opencv2/opencv_modules.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc.hpp"

using namespace cv;
using namespace std;

int main()
{
//create a grey scale image with black background
Mat image(600,600, CV_8UC1, Scalar(0)), detected_edges(600,600, CV_8UC1, Scalar(0));

//variables for canny
int lower_threshold = 50;
int kernel_size = 3;

//variables for contours
vector <vector<Point>> contours;
vector <Vec4i> hierarchy;

//variables for drawContours
Mat canvas(600, 600, CV_8UC1,Scalar(0));

//create a level-1 rectangle with four points
Point p[4];
p[0] = Point(20,20);
p[1] = Point(20, 580);
p[2] = Point(280, 580);
p[3] = Point(280,20);

fillConvexPoly(image, p, 4, Scalar(255));

//create a level-1 rectangle with four points

p[0] = Point(300,20);
p[1] = Point(300, 580);
p[2] = Point(580, 580);
p[3] = Point(580,20);

fillConvexPoly(image, p, 4, Scalar(255));

//create a level-2 rectangle
p[0] = Point(40,40);
p[1] = Point(40, 560);
p[2] = Point(150, 560);
p[3] = Point(150,40);

fillConvexPoly(image, p, 4, Scalar(0));

//create a level-3 rectangle
p[0] = Point(60,240);
p[1] = Point(60, 340);
p[2] = Point(120, 340);
p[3] = Point(120,240);

fillConvexPoly(image, p, 4, Scalar(255));

//create a level-2 rectangle
p[0] = Point(160,40);
p[1] = Point(160, 560);
p[2] = Point(270, 560);
p[3] = Point(270,40);

fillConvexPoly(image, p, 4, Scalar(0));

//create a level-3 rectangle
p[0] = Point(180,80);
p[1] = Point(180, 260);
p[2] = Point(250, 260);
p[3] = Point(250,80);

fillConvexPoly(image, p, 4, Scalar(255));

//create a level-3 rectangle
p[0] = Point(190,310);
p[1] = Point(190, 500);
p[2] = Point(260, 500);
p[3] = Point(260,310);

fillConvexPoly(image, p, 4, Scalar(255));

//create a level-4 rectangle
p[0] = Point(200,350);
p[1] = Point(200, 460);
p[2] = Point(250, 460);
p[3] = Point(250,350);

fillConvexPoly(image, p, 4, Scalar(0));

imshow("Image",image);

imwrite("contours.jpg",image);

Canny(image,detected_edges,lower_threshold,lower_threshold*3,kernel_size);

findContours(detected_edges,contours,hierarchy,CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE);

// Draw contours
for(int i=0; i < contours.size();i++)
{
drawContours(canvas,contours,i,Scalar(255),2,8,hierarchy,0,Point());
imshow("contours",canvas);
while(1)
{
char k = waitKey(33);
if(k == 27)
break;
}
}
}
