#ifndef VECTOR_2D
#define VECTOR_2D

#include <iostream>
using namespace std;

class Vector2D
{
	public:
	// Variable Declarations:
	double x;
	double y;
	// Constructor(s):
	Vector2D(); // Default
	Vector2D(double in_x, double in_y);
};

Vector2D operator * (Vector2D, double);
ostream& operator << (ostream&, Vector2D);

#endif