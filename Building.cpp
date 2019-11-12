#include <iostream>
#include "Point2D.h"
#include "GameObject.h"
#include "Building.h"
using namespace std;

// Constructors
Building::Building(): GameObject('B') // default
{
	// Variable initialization	
	pokemon_count = 0;
	// Announcement
	cout << "Building default constructed" << endl;
}

Building::Building(Point2D in_loc, int in_id, chat in_code): GameObject(in_loc, in_id, in_code)
{
	// Variable Initialization
	location = in_loc;
	id_num = in_id;
	display_code = in_code;
	state = 0;
	// Announcement
	cout << "Building constructed" << endl;
}
