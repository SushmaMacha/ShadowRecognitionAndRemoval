/*
Authour - Sushma Macha
Function Implementations 
findLevel - gives information of the level of a given contour in a contour hierarchy
findChildren - returns the number of children in a given contour sub tree 
formed with the root as the parameter contour id passed to the function
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "opencv2/opencv_modules.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc.hpp"

using namespace cv;
using namespace std;

class contourLeafs{

public:	
	
vector <Vec4i> hierarchy;
int level;

contourLeafs(vector <Vec4i> &H)
{
	hierarchy = H;
	level = 0;
	//children = 0;
}

//Find the level at which the contour is
/*
Parameter id is the contour id obtained from the function findContours
*/
int findLevel(int id)
{
	level = 0;
	int i = id;
	while(hierarchy[i][3] != -1)
	{
		i = hierarchy[i][3];
		level++;
	}
	return level;
		
}

//Find the number of leafs a contour has
/*
The parameter children is passed by address and captures the number of children of each contour
The parameter i is the id of the contour - obtained from the function findContours
*/
int findChildren(int i, int &children)
{
	// Loop till there is no child contour
	while(hierarchy[i][2] != -1)
	{
		i = hierarchy[i][2];
		//cout << "child : " << i << endl;
		children++;
		// Check for sibling contour
		if(hierarchy[i][0] != -1)
		{
			children++;
			//cout << "sibling : " << hierarchy[i][0] << endl;
			// Check for the children of the sibling contour as well
			findChildren(hierarchy[i][0], children);
		}
	}
	return children;
}

//Print the hierarchy of the contours - debugging purposes
void printHierarchy(void)
{
	for(int i = 0;i< hierarchy.size();i++)
		cout << hierarchy[i][0] <<  " " << hierarchy[i][1] << " " << hierarchy[i][2] << " " << hierarchy[i][3] << endl;
}

};
