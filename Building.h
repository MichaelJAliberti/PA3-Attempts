#ifndef BUILDING
#define BUILDING

#include "Point2D.h"
#include "GameObject.h"
using namespace std;

// Class
class Building: public GameObject
{
private:
	// Private variables
	int pokemon_count;
public:
	// Public constructors
	Building(); // Default constructor
	Building(char in_code, int in_id, Point2D in_loc);
	// Public functions
	//void AddOnePokemon();
	//void RemoveOnePokemon();
	//void ShowStatus();
	//bool ShouldBeVisible();
};

#endif
