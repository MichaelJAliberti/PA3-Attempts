#include <iostream>
#include "Point2D.h"
#include "GameObject.h"
#include "PokemonCenter.h"
#include "PokemonGym.h"
#include "Pokemon.h"
#include "Model.h"
#include "View.h"
using namespace std;


// Contructor
Model::Model()
{
	// Initialize variables
	time = 0;
	num_objects = 6;
	num_pokemon = 2;
	num_centers = 2;
	num_gyms = 2;
	// Pokemon 1
	Pokemon* Pokemon1 = new Pokemon("Pikachu", 1, 'P', 2, Point2D(5, 1));
	object_ptrs[0] = Pokemon1;
	pokemon_ptrs[0] = Pokemon1;
	// Pokemon 2
	Pokemon* Pokemon2 = new Pokemon("Bulbasaur", 2, 'P', 1, Point2D(10, 1));
	object_ptrs[1] = Pokemon2;
	pokemon_ptrs[1] = Pokemon2;
	// PokemonCenter 1
	PokemonCenter* PokemonCenter1 = new PokemonCenter(1, 1, 100, Point2D(1, 20));
	object_ptrs[2] = PokemonCenter1;
	center_ptrs[0] = PokemonCenter1;
	// PokemonCenter 2
	PokemonCenter* PokemonCenter2 = new PokemonCenter(2, 2, 200, Point2D(10, 20));
	object_ptrs[3] = PokemonCenter2;
	center_ptrs[1] = PokemonCenter2;
	// PokemonGym 1 (supposed to be default but this aligns better with sample output)
	PokemonGym* PokemonGym1 = new PokemonGym(10, 1, 2.0, 3, 1, Point2D(0, 0));
	object_ptrs[4] = PokemonGym1;
	gym_ptrs[0] = PokemonGym1;
	// PokemonGym 2
	PokemonGym* PokemonGym2 = new PokemonGym(20, 5, 7.5, 8, 2, Point2D(5, 5));
	object_ptrs[5] = PokemonGym2;
	gym_ptrs[1] = PokemonGym2;
	// Announcement
	cout << "Model default constructed." << endl;
}


// Destructor
Model::~Model()
{
	for (int i = 0; i <= 5; i++)
		delete object_ptrs[i];
	cout << "Model destructed." << endl;
}


// Public member functions
Pokemon* Model::GetPokemonPtr(int id)
{
	// Returns a Pokemon pointer that corresponds to the given id

	return pokemon_ptrs[id - 1];
}

PokemonCenter* Model::GetPokemonCenterPtr(int id)
{
	// Returns a PokemonCenter pointer which corresponds to the given id

	return center_ptrs[id - 1];
}

PokemonGym* Model::GetPokemonGymPtr(int id)
{
	// Returns a PokemonGym pointer which corresponds to the given id

	return gym_ptrs[id - 1];
}

bool Model::Update()
{
	// Increment time
	time++;
	// Temporary truth holder
	bool tempTruth = false;
	// Update all and see if any yield true
	for (int i = 0; i <= 5; i++)
		if (object_ptrs[i]->Update())
		{
			tempTruth = true;
		}
	// Return true immediately if any updates are true; oterwise, check win/fail states
	if (tempTruth)
		return true;
	else if (gym_ptrs[0]->IsBeaten() && gym_ptrs[1]->IsBeaten())
	{
		cout << "GAME OVER: You win! All Pokemon Gyms beaten!" << endl;
		exit(0);
	}
	else if (pokemon_ptrs[0]->IsExhausted() && pokemon_ptrs[1]->IsExhausted())
	{
		// Dude you suck uninstall the game
		cout << "GAME OVER: You lose! All of your Pokemon are tired!" << endl;
		exit(0);
	}
}

void Model::Display(View& view)
{
	// Graph objects
	view.Clear();
	for (int i = 0; i < num_objects; i++)
		view.Plot(object_ptrs[i]);
	view.Draw();
}

void Model::ShowStatus()
{
	// Outputs the status of all GameObjects by calling their ShowStatus() functions

	// Output time
	cout << "Time: " << time << endl;
	// Show status per object 
	for (int i = 0; i <= 5; i++)
		object_ptrs[i]->ShowStatus();
}