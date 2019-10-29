#include <iostream>
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

ostream& operator << (ostream& out, Point2D pt);
