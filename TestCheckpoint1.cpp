#include <iostream>
#include "Point2D.h"
#include "Vector2D.h"
#include "GameObject.h"

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
	cout << (p1 + v1) << endl;
	cout << (p1 - p2) << endl;
	cout << (v1/2) << " " << v1*2 << endl;

	cout << v3 << endl;
	
	GameObject g1(p1, 3, 'z');
	cout << g1.GetLocation() << endl;
	cout << g1.GetId() << endl;
	cout << g1.GetState() << endl;
	g1.ShowStatus();
	

	return 0;
}
