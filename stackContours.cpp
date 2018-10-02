#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class Stack
{

public:
	int noOfElts;
	int sptr;
	bool empty;
	bool full;
	int *hierarchy = nullptr;


Stack(int n)
{
	noOfElts = n;
	sptr = 0;
	empty = true;
	full = false;
	hierarchy = (int *)malloc(n*sizeof(int));
}

int pop()
{
if(!empty)
{
	sptr--;
	if(sptr <= 0) 
		empty = true;
	return *(hierarchy+sptr);
}
else
	cout << "Stack Empty" << endl;
return -1;
}

void push(int n)
{
	if(!full)
	{
		*(hierarchy+sptr) = n;
		if(empty) empty = false;
		if(sptr == noOfElts)
		{
			cout << "Stack Full" << endl;
			full = true;
		}
		else
			sptr++;
	}
		
}

void printStack(void)
{
cout << "Printing the stack Elements: " << endl;
for(int i = 0; i < sptr;i++)
{
	cout << hierarchy[i] << endl;
}
}
};
