#include <iostream>
#include "Vector2D.h"
using namespace std;

// Constructors
Vector2D::Vector2D() // Default
{
	x = 0;
	y = 0;		
}


Vector2D::Vector2D(double in_x, double in_y)
{
	x = in_x;
	y = in_y;
}


// Non-MemberOverloaded Operators
Vector2D::Vector2D operator * ()
