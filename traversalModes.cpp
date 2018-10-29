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

#define debug 1

class traversalModes
{
	public:	
	vector <vector<Point>> contours;
	vector <Vec4i> hierarchy;
	int sz=0,maxLevel=0;
	//array storing each contour level
	int *Clevel;
	Stack *s;
	bool parent;
	
	traversalModes(vector <vector<Point>> &C,vector <Vec4i> &H,int n)
	{
		contours = C;
		hierarchy = H;
		Clevel = (int *)malloc(n*sizeof(int));
		sz = n;
		memset(Clevel,-1,sz*4);
		s = new Stack(sz);
		parent = false;
	}
	
	void contourLevels(void)
	{
		int i = 0, j = 0,level = 0;
		//by default in TREE mode contour 0 is of level 0
		Clevel[0] = 0;
		while(1)
		{
			//check for a child contour
			//if a child contour exists
			if(hierarchy[i][2] != -1 && Clevel[hierarchy[i][2]] == -1)
			{
				//update the level
				Clevel[hierarchy[i][2]] = ++level;
				//store the maximum level for future use
				if(level > maxLevel)
					maxLevel = level;
				//point to the child contour
				i = hierarchy[i][2];
				//continue
				continue;
			}
			//if not check for a sibling contour
			if(hierarchy[i][0] != -1 && Clevel[hierarchy[i][0]] == -1)
			{
				//add same level to sibling
				Clevel[hierarchy[i][0]] = level;
				//point to the sibling contour
				i = hierarchy[i][0];
				//continue
				continue;
			}
			//if there is parent contour
			else if(hierarchy[i][3] != -1)
			{
				//point to the parent contour till there is a sibling contour, update level
				while(hierarchy[i][3] != -1)
				{
					i = hierarchy[i][3];level--;
					if(hierarchy[i][0] != -1 && Clevel[hierarchy[i][0]] == -1)
					{
						//add same level to sibling
						Clevel[hierarchy[i][0]] = level;
						//point to sibling contour
						i = hierarchy[i][0];
						//continue
						break;
					}
				}
			}
			//if no child, no sibling and no parent
			else
				break;
		}
		cout << " Max Level : " << maxLevel << endl;
	}
	
	//Validate if all the contours are visitied
	void validateVisits(void)
	{
		int i = 0;
		for(i = 0; i < sz;i++)
			if(Clevel[i] == -1)
				cout << "Missed a contour " << endl;
		if(i == sz)
			cout << "Identified levels of all contours successfully" << endl;
	}
	
	//Breadth First Search
	void BFS(void)
	{
		//variables for drawContours
		Mat canvas(650, 1160, CV_8UC3,Scalar(0,0,0));	
		int temp = 0,level = 0,i=0,j=0;
		while(level <= maxLevel)
		{
			for(int i = 0; i < sz;i++)
			{
				if(Clevel[i] == level)
				{
					drawContours(canvas,contours,i,Scalar(255),2,8,hierarchy,0,Point());
					namedWindow("BFS", WINDOW_AUTOSIZE);
					imshow("BFS",canvas);
					while(1)
					{
						char k = waitKey(33);
						if(k == 27)
							break;
					}
				}
					
			}
			level++;
			
		}
		
	}
	//Depth First Search
	void DFS(void)
	{
		//variables for drawContours
		Mat canvas(650, 1160, CV_8UC3,Scalar(0,0,0));
		int i = 0, j = 0,temp=0;
		while(1)
		{
			//check for a child contour
			//if a child contour exists
			if(hierarchy[i][2] != -1)
			{
				//Store the next contour in stack 
				if(hierarchy[i][0] != -1)
					s->push(hierarchy[i][0]);
				//point to the child contour
				i = hierarchy[i][2];
				drawContours(canvas,contours,i,Scalar(255),2,8,hierarchy,0,Point());
				namedWindow("DFS", WINDOW_AUTOSIZE);
				imshow("DFS",canvas);
				while(1)
				{
					char k = waitKey(33);
					if(k == 27)
						break;
				}
				continue;
			}
			//if not check for a sibling contour
			if(hierarchy[i][0] != -1)
			{
				i = hierarchy[i][0];
				drawContours(canvas,contours,i,Scalar(255),2,8,hierarchy,0,Point());
				namedWindow("DFS", WINDOW_AUTOSIZE);
				imshow("DFS",canvas);
				while(1)
				{
					char k = waitKey(33);
					if(k == 27)
						break;
				}
				//continue
				continue;
			}
			//if there is parent contour
			else if(!s->empty)
			{
				//point to the sibling contour
				i = s->pop();	
				drawContours(canvas,contours,i,Scalar(255),2,8,hierarchy,0,Point());
				namedWindow("DFS", WINDOW_AUTOSIZE);
				imshow("DFS",canvas);
				while(1)
				{
					char k = waitKey(33);
					if(k == 27)
						break;
				}
				//continue
				continue;
				//else
					//break;
			}
			//if no child, no sibling and no parent
			else
				break;
		}
		cout << " Max Level : " << maxLevel << endl;
		
	}
	//
	void childToParentDFS(void)
	{
		
		//variables for drawContours
		Mat canvas(650, 1160, CV_8UC3,Scalar(0,0,0));
		int i = 0, j = 0,temp=0;
		while(1)
		{
			//check for a child contour
			//if a child contour exists
			if(hierarchy[i][2] != -1)
			{
				//point to the child contour
				while(hierarchy[i][2] != -1)
				{
					i = hierarchy[i][2];
				}
				//point to next
				cout << "child" << i << endl;
				//if the child has next
				if(hierarchy[i][0] != -1)
				{
					//point to next
					i = hierarchy[i][0];
					cout << "next of child" << i << endl;
				}
				//print the child
				drawContours(canvas,contours,i,Scalar(255),2,8,hierarchy,0,Point());
				namedWindow("IDFS", WINDOW_AUTOSIZE);
				imshow("IDFS",canvas);
				while(1)
				{
					char k = waitKey(33);
					if(k == 27)
						break;
				}
				continue;
			}
			//if there is parent contour
			else if(hierarchy[i][3] != -1)
			{
				//draw the child contour
				drawContours(canvas,contours,i,Scalar(255),2,8,hierarchy,0,Point());
				namedWindow("IDFS", WINDOW_AUTOSIZE);
				imshow("IDFS",canvas);
				while(hierarchy[i][3] != -1)
				{
					
					//point to parent
					i = hierarchy[i][3];
					cout << "parent " << i << endl;
					//draw parent contour
					drawContours(canvas,contours,i,Scalar(255),2,8,hierarchy,0,Point());
					namedWindow("IDFS", WINDOW_AUTOSIZE);
					imshow("IDFS",canvas);
					while(1)
					{
						char k = waitKey(33);
						if(k == 27)
							break;
					}
					//if parent has next
					if(hierarchy[i][0] != -1)
						break;
					//if the parent has previous
					if(hierarchy[i][1] != -1)
					{
						i = hierarchy[i][1];
						// print previous
						drawContours(canvas,contours,i,Scalar(255),2,8,hierarchy,0,Point());
						namedWindow("IDFS", WINDOW_AUTOSIZE);
						imshow("IDFS",canvas);
						while(1)
						{
							char k = waitKey(33);
							if(k == 27)
								break;
						}
						//point to next
						cout << "previous of parent " << i << endl;
						continue;
					}
					
				}
				if(hierarchy[i][0] != -1)
				{
					//point to next
					i = hierarchy[i][0];
					cout << "next of parent " << i << endl;
					//if no child
					if(hierarchy[i][2] == -1)
					{
						drawContours(canvas,contours,i,Scalar(255),2,8,hierarchy,0,Point());
						namedWindow("IDFS", WINDOW_AUTOSIZE);
						imshow("IDFS",canvas);
						while(1)
						{
							char k = waitKey(33);
							if(k == 27)
								break;
						}
					}
					
					continue;
				}
				else
				{
					//draw contour
					drawContours(canvas,contours,i,Scalar(255),2,8,hierarchy,0,Point());
					namedWindow("IDFS", WINDOW_AUTOSIZE);
					imshow("IDFS",canvas);
					while(1)
					{
						char k = waitKey(33);
						if(k == 27)
							break;
					}
					break;
				}
			}
			//if not check for a sibling contour
			if(hierarchy[i][0] != -1)
			{
				i = hierarchy[i][0];
				cout << "next " << i << endl;
				/*drawContours(canvas,contours,i,Scalar(255),2,8,hierarchy,0,Point());
				namedWindow("IDFS", WINDOW_AUTOSIZE);
				imshow("IDFS",canvas);
				while(1)
				{
					char k = waitKey(33);
					if(k == 27)
						break;
				}
				//continue*/
				continue;
			}			
			//if no child, no sibling and no parent
			else
			{
				//draw the contour
				drawContours(canvas,contours,i,Scalar(255),2,8,hierarchy,0,Point());
				namedWindow("IDFS", WINDOW_AUTOSIZE);
				imshow("IDFS",canvas);
				while(1)
				{
					char k = waitKey(33);
					if(k == 27)
						break;
				}
				break;
			}
		}
	}
	
	void IDFS(void)
	{
		//save the first contour as parent
		//loop through next and push in a stack
		//while there is a child
		//point to the parent contour
		//check for a child - point to the child
		//goto step 2
		//if no child, print parent till it reaches parent
		//pop - save parent
		//goto step 2
		
		
		Stack s(contours.size());
		int i = 0, parent = 0, j= 0,current = 0,iter=0;
		Mat canvas(650, 1160, CV_8UC3,Scalar(0,0,0));
		while(1)
		{
			//loop through next and push in a stack
			j = current;
			#if debug 
				cout << "Iteration # : " << ++iter << endl;
			#endif
			//push all the contours in same level into stack
			while(hierarchy[current][0] != -1)
			{
				#if debug 
					cout << "Stack Push : " << current << endl;
				#endif
				s.push(hierarchy[current][0]);
				current = hierarchy[current][0];
			}
			current = j;
			//If the current contour has children, go to the deepest one
			if(hierarchy[current][2] != -1)
				current = hierarchy[current][2];
			//else draw contours from child to parent or just parent
			else
			{
				//draw contours from child to parent
				while(current != parent && hierarchy[current][3] != -1)
				{
					#if debug 
						cout << "Child : " << current << endl;
					#endif
					drawContours(canvas,contours,current,Scalar(255),2,8,hierarchy,0,Point());
					namedWindow("IDFS", WINDOW_AUTOSIZE);
					imshow("IDFS",canvas);
					while(1)
					{
						char k = waitKey(33);
						if(k == 27)
							break;
					}
					current = hierarchy[current][3];
				}
				//draw parent
				#if debug 
					cout << "Parent : " << current << endl;
				#endif
				drawContours(canvas,contours,current,Scalar(255),2,8,hierarchy,0,Point());
				namedWindow("IDFS", WINDOW_AUTOSIZE);
				imshow("IDFS",canvas);
				while(1)
				{
					char k = waitKey(33);
					if(k == 27)
						break;
				}
			
				parent = s.pop();
				#if debug 
					cout << "Stack Pop : " << parent << endl;
				#endif
				if(hierarchy[parent][2] != -1)
					current = hierarchy[parent][2];
				else
				{
					while((hierarchy[parent][2] == -1 && !s.empty)||(parent == 0))
					{
						#if debug
							cout << "Next : " << parent << endl;
						#endif
						drawContours(canvas,contours,parent,Scalar(255),2,8,hierarchy,0,Point());
						namedWindow("IDFS", WINDOW_AUTOSIZE);
						imshow("IDFS",canvas);
						while(1)
						{
							char k = waitKey(33);
							if(k == 27)
								break;
						}
						parent = s.pop();
					}
					if(hierarchy[parent][2] != -1)
						current = hierarchy[parent][2];
				}	
					
			}
			
			//break condition
			if(s.empty && hierarchy[parent][2] == -1)
				break;		
		}
		
		
	}
	
	//Breadth first search from the inner most level to outer most level
	void childToParentBFS(void)
	{
		//variables for drawContours
		Mat canvas(650, 1160, CV_8UC3,Scalar(0,0,0));	
		int temp = 0,level = maxLevel,i=0,j=0;
		while(level >= 0)
		{
			for(int i = 0; i < sz;i++)
			{
				if(Clevel[i] == level)
				{
					drawContours(canvas,contours,i,Scalar(255),2,8,hierarchy,0,Point());
					namedWindow("IBFS", WINDOW_AUTOSIZE);
					imshow("IBFS",canvas);
					while(1)
					{
						char k = waitKey(33);
						if(k == 27)
							break;
					}
				}
					
			}
			level--;
			
		}
	}
	
};
