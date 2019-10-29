#include <iostream>
#include "Point2D.h"
//#include "Vector2d.h"

using namespace std;

int main()
{
		
	Point2D p1;
	p1.x = 1;
	p1.y = 1;

	Point2D p2;
	p2.x = 5;
	p2.y = 5;

	double distance = GetDistanceBetween(p1, p2);

	cout << distance << endl;
	cout << p1 << " " << p2 << endl;
	
	return 0;
}
