#ifndef POINT_2D
#define POINT_2D

#include <iostream>
#include "Vector2D.h"
using namespace std;

class Point2D
{
	public:
	// Variable Declarations:
	double x;
	double y;
	// Constructor(s):
	Point2D(); // Default
	Point2D(double in_x, double in_y);
};

double GetDistanceBetween(Point2D, Point2D);

ostream& operator << (ostream&, Point2D);
Point2D operator + (Point2D, Vector2D);

#endif