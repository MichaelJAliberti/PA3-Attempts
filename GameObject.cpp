#include <iostream>
#include "Point2D.h"
#include "GameObject.h"
using namespace std;

// Constructors
GameObject::GameObject(char in_code)
{
	// Variable initialization
	id_num = 1;
	display_code = in_code;
	state = 0;
	// Announcement
	cout << "GameObject constructed." << endl;
}

GameObject::GameObject(Point2D in_loc, int in_id, char in_code)
{
	// Variable initialization	
	location = in_loc;	
	id_num = in_id;
	display_code = in_code;
	state = 0;
	// Announcement
	cout << "GameObject constructed." << endl;
}


// Member Functions
Point2D GameObject::GetLocation()
{
	// Returns the location of the GameObject
	
	return this->location;
}

int GameObject::GetId()
{
	// Returns the id_num of the GameObject

	return this->id_num;
}

bool GameObject::GetState()
{
	// Returns the state of the GameObject

	return this->state;
}

void GameObject::ShowStatus()
{
	// Prints the status of the GameObject 	

	cout << this->display_code << " Status: " << this->id_num 
	<< " located at " << this->location << endl;
}
