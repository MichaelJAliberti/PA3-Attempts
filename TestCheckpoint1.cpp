#include <iostream>
#include "Point2D.h"
#include "Vector2D.h"
//#include "Vector2d.h"

using namespace std;

int main()
{
		
	Point2D p1(1,1);
	Point2D p2(5,5);

	Vector2D v1(2,3);
	double d = 2;

	double distance = GetDistanceBetween(p1, p2);
	Vector2D v3 = v1 * 2;

	cout << distance << endl;
	cout << p1 << " " << p2 << endl;

	cout << v3 << endl;
	
	return 0;
}
