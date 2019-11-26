#ifndef MODEL
#define MODEL

#include "Point2D.h"
#include "Vector2D.h"
#include "GameObject.h"
#include "PokemonCenter.h"
#include "PokemonGym.h"
#include "Pokemon.h"
#include "View.h"

// Class
class Model
{
public:
	// Private Mamber Variables
	int time;
	GameObject* object_ptrs[10];
	int num_objects;
	Pokemon* pokemon_ptrs[10];
	int num_pokemon;
	PokemonCenter* center_ptrs[10];
	int num_centers;
	PokemonGym* gym_ptrs[10];
	int num_gyms;
	// Private copy constructor
public:
	// Public constructors
	Model();
	// Destructor
	~Model();
	// Public member functions
	Pokemon* GetPokemonPtr(int id);
	PokemonCenter * GetPokemonCenterPtr(int id);
	PokemonGym * GetPokemonGymPtr(int id);
	bool Update();
	void Display(View& view);
	void ShowStatus();
};

#endif