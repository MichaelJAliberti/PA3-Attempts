#include <iostream>
#include <string>
#include <math.h>
#include <cstdlib>
#include <ctime>
#include "Point2D.h"
#include "Vector2D.h"
#include "GameObject.h"
#include "PokemonCenter.h"
#include "PokemonGym.h"
#include "Pokemon.h"
using namespace std;

// Constructors
Pokemon::Pokemon(): GameObject('P') // default
{
	// Variable inititialization
	speed = 5;
	stamina = 20;
	experience_points = 0;
	pokemon_dollars = 0;
	// Added initializations
	training_units_to_buy = 0;
	stamina_points_to_buy = 0;
	current_center = NULL;
	current_gym	= NULL;;
	name = "Default Pokemon";
	// Announcement
	cout << "Pokemon default constructed." << endl;
}

Pokemon::Pokemon(char in_code): GameObject(in_code)
{
	// Variable inititialization
	speed = 5;
	stamina = 20;
	experience_points = 0;
	pokemon_dollars = 0;
	// Added initializations
	training_units_to_buy = 0;
	stamina_points_to_buy = 0;
	current_center = NULL;
	current_gym	= NULL;
	name = "Less Default Pokemon";
	// Announcement
	cout << "Pokemon constructed." << endl;
}

Pokemon::Pokemon(string in_name, int in_id, char in_code, unsigned int in_speed, Point2D in_loc): GameObject(in_loc, in_id, in_code)
{
	// Variable inititialization
	speed = in_speed;
	stamina = 20;
	experience_points = 0;
	pokemon_dollars = 0;
	name = in_name;
	// Added initializations
	training_units_to_buy = 0;
	stamina_points_to_buy = 0;
	current_center = NULL;
	current_gym	= NULL;
	// Announcement
	cout << "Pokemon constructed." << endl;
}


// Destructor
Pokemon::~Pokemon()
{
	cout << "Pokemon destructed." << endl;
}


// Public member functions
void Pokemon::StartMoving(Point2D dest)
{
	// Tells the Pokemon to start moving

	// Set destination
	Pokemon::SetupDestination(dest);
	// Check if at location or exhausted; if not, set state to MOVING
	if (location.x == dest.x && location.y == dest.y)
		cout << display_code << id_num << ": I'm already there. See?" << endl;
	else if (state == EXHAUSTED)
		cout << display_code << id_num << ": I am exhausted. I may move but you cannot see me." << endl;
	else
	{
		state = MOVING;
		cout << display_code << id_num << ": On my way." << endl;
	}
	return;
}

void Pokemon::StartMovingToCenter(PokemonCenter* center)
{
	// Tells the Pokemon to start moving to a PokemonCenter

	// Check if at center or exhausted; if not, set state to MOVING_TO_CENTER
	if (location.x == (center->GetLocation()).x && location.y == (center->GetLocation()).y)
	{
		// Set target if arrived by normal movement
		current_center = center;
		cout << display_code << id_num << ": I'm already at the Pokemon Center!" << endl;
	}
	else if (state == EXHAUSTED)
		cout << display_code << id_num << ": I am exhausted so I can’t move to recover stamina…" << endl;
	else
	{
		// Set destination
		Pokemon::SetupDestination(center->GetLocation());
		current_center = center;
		state = MOVING_TO_CENTER;
		cout << display_code << id_num << ": On my way to center " << center->GetId() << "." << endl;
	}
	return;
}

void Pokemon::StartMovingToGym(PokemonGym* gym)
{
	// Tells the Pokemon to start moving to a PokemonGym

	// Check if at center or exhausted; if not, set state to MOVING_TO_CENTER
	if (location.x == (gym->GetLocation()).x && location.y == (gym->GetLocation()).y)
	{
		// Establish current gym if got there via normal movement
		current_gym = gym;
		cout << display_code << id_num << ": I'm already at the Pokemon Gym!" << endl;
	}
	else if (state == EXHAUSTED)
		cout << display_code << id_num << ": I am exhausted so I shouldn’t be going to the gym…" << endl;
	else
	{
		// Set destination
		Pokemon::SetupDestination(gym->GetLocation());
		current_gym = gym;
		state = MOVING_TO_GYM;
		cout << display_code << id_num << ": On my way to gym " << gym->GetId() << "." << endl;
	}
	return;
}

void Pokemon::StartTraining(unsigned int num_training_units)
{
	// Tells the Pokemon to start training (num_training_units) in a PokemonGym
	// Call in Update()

	// Check conditions
	if (state == EXHAUSTED)
		// Ensure not exhausted
		cout << display_code << id_num << ": I am exhausted so no more training for me..."  << endl;
	else if (state != IN_GYM)
		// Ensure in gym
		cout << display_code << id_num << ": I can only train in a Pokemon Gym!" << endl;
	else if (!current_gym->IsAbleToTrain(num_training_units, pokemon_dollars, stamina))
		cout << display_code << id_num << ": Not enough stamina and/or money for training" << endl;
	else if (current_gym->GetState() == BEATEN)
		// Ensure gym is not beaten
		cout << display_code << id_num << ": Cannot train! This Pokemon Gym is already beaten!" << endl;
	else
	{
		// If able to train, change state and determine number to buy
		state = TRAINING_IN_GYM;
		cout << display_code << id_num << ": Started " << num_training_units << " training unit(s) at Pokemon Gym " << current_gym->GetId() << endl;
		if (current_gym->GetNumTrainingUnitsRemaining() < num_training_units)
			training_units_to_buy = current_gym->GetNumTrainingUnitsRemaining();
		else
			training_units_to_buy = num_training_units;
	}
	return;
}

void Pokemon::StartRecoveringStamina(unsigned int num_stamina_points)
{
	// Tells the Pokemon to start recovering at a PokemonCenter

	// Check Conditions
	if (state != IN_CENTER)
		// Ensure in center
		cout << display_code << id_num << ": I can only recover stamina at a Pokemon Center!" << endl;
	else if (current_center->GetNumStaminaPointsRemaining() < 1)
		// Ensure stamina remains
		cout << display_code << id_num << ": Cannot recover! No stamina points remaining in this Pokemon Center" << endl;
	else if (!current_center->CanAffordStaminaPoints(num_stamina_points, pokemon_dollars))
		// Ensure affordable healthcare
		cout << display_code << id_num << ": Not enough money to recover stamina." << endl;
	else
	{
		// If able, change state and determine points to buy
		state = RECOVERING_STAMINA;
		cout << display_code << id_num << ": Started recovering " << num_stamina_points	 << " stamina point(s) at Pokemon Center " << current_center->GetId() << endl;
		if (current_center->GetNumStaminaPointsRemaining() < num_stamina_points	)
			stamina_points_to_buy = current_center->GetNumStaminaPointsRemaining();
		else
			stamina_points_to_buy = num_stamina_points;
	}
}

void Pokemon::Stop()
{
	// Tells this Pokemon to stop doing whatever it was doing

	state = STOPPED;
	cout << display_code << id_num << ": Stopping..." << endl;
}

bool Pokemon::IsExhausted()
{
	// Returns true if stamina is 0

	if (stamina == 0)
		return true;
	else
		return false;
}

bool Pokemon::ShouldBeVisible()
{
	// Returns true if this Pokemon is Not exhausted

	if (state != EXHAUSTED)
		return true;
	else
		return false;
}

void Pokemon::ShowStatus()
{
	// Prints information about pokemon behavior

	// Basic info
	cout << name << " status: ";
	GameObject::ShowStatus();
	// Behavioral info
	switch (state)
	{
		case STOPPED:
			cout << " stopped" << endl;
			break;
		case MOVING:
			cout << " moving at a speed of " << speed << " to " << destination << " at each step of " << delta << endl;
			break;
		// Nothing if exhausted
		case IN_GYM:
			cout << " inside Pokemon Gym " << current_gym->GetId() << endl;
		case IN_CENTER:
			cout << " inside Pokemon Center " << current_center->GetId() << endl;
			break;
		case MOVING_TO_GYM:
			cout << " heading to Pokemon Gym " << current_gym->GetId() << " at a speed of " << speed << " at each step of " << delta << endl;
			break;
		case MOVING_TO_CENTER:
			cout << " heading to Pokemon Center " << current_center->GetId() << " at a speed of " << speed << " at each step of " << delta << endl;
			break;
		case TRAINING_IN_GYM:
			cout << " training in Pokemon Gym " << current_gym->GetId() << endl;
			break;
		case RECOVERING_STAMINA:
			cout << " recovering stamina in Pokemon Center " << current_center->GetId() << endl;
			break;
	}
	cout << "\tStamina: " << stamina << endl;
	cout << "\tPokemon Dollars: " << pokemon_dollars << endl;
	cout << "\tExperience Points: " << experience_points << endl;
}

bool Pokemon::Update()
{
	
	// Preliminaries
	if (state != EXHAUSTED)	
		if (Pokemon::IsExhausted())
		{
			state = EXHAUSTED;
			cout << name << " is out of stamina and can't move." << endl;
			return true;
		}

	switch (state)
	{
		case STOPPED:
			return false;
			break;
		case MOVING:
			if (Pokemon::UpdateLocation())
			{
				state = STOPPED;
				return true;
			}
			break;
		case EXHAUSTED:
			return false;
			break;
		case IN_GYM:
			return false;
			break;
		case IN_CENTER:
			return false;
			break;
		case MOVING_TO_GYM:
			if (Pokemon::UpdateLocation())
			{
				state = IN_GYM;
				is_in_gym = true;
				current_gym->AddOnePokemon();
				return true;
			}
			break;
		case MOVING_TO_CENTER:
			if (Pokemon::UpdateLocation())
			{
				state = IN_CENTER;
				is_in_center = true;
				current_center->AddOnePokemon();
				return true;
			}
			break;
		case TRAINING_IN_GYM:
			// Change Pokemon values based on training regimen
			stamina -= current_gym->GetStaminaCost(training_units_to_buy);
			pokemon_dollars	-= current_gym->GetDollarCost(training_units_to_buy);
			experience_points += current_gym->TrainPokemon(training_units_to_buy);
			// Output message
			cout << "** " << name << " completed " << training_units_to_buy << " training unit(s)!**" << endl;
			cout << "** " << name << " gained " << current_gym->TrainPokemon(training_units_to_buy) << " experience point(s)!**" << endl;
			// Change state and revert training_units_to_buy
			state = IN_GYM;
			training_units_to_buy = 0;
			return true;
			break;
		case RECOVERING_STAMINA:
			// Change pokemon values based on health insurance policy
			stamina += current_center->DistributeStamina(stamina_points_to_buy);
			pokemon_dollars -= current_center->GetDollarCost(stamina_points_to_buy);
			// Output message
			cout << "** " << name << " recovered " << stamina_points_to_buy << " stamina point(s)!**" << endl;
			// Change state and revert tamina_points_to_buy
			state = IN_CENTER;
			stamina_points_to_buy = 0;
			return true;
			break;
	}
}


// Protected member functions
bool Pokemon::UpdateLocation()
{
	// Updates the object’s location while it is moving

	// Check if within 1 step
	if (fabs(destination.x - location.x) <= delta.x && fabs(destination.y - location.y) <= delta.y)
	{
		location = destination;
		cout << display_code << id_num << ": I'm there!" << endl;
		return true;
	}
	else
	{
		location = location + delta;
		stamina--;
		pokemon_dollars += GetRandomAmountOfPokemonDollars();
		cout << display_code << id_num << ": step..." << endl;
		return false;
	}
}

void Pokemon::SetupDestination(Point2D dest)
{
	// Sets up the object to start moving to destination

	// Set destination and calculate delta
	destination = dest;
	delta = (destination - location) * (speed / GetDistanceBetween(destination, location));
	// Change status if currently in a building
	if (is_in_center)
	{
		current_center->RemoveOnePokemon();
		is_in_center = false;
	}
	if (is_in_gym)
	{
		current_gym->RemoveOnePokemon();
		is_in_gym = false;
	}
	return;
}


// Nonmember functions
double GetRandomAmountOfPokemonDollars()
{
	// Returns a random number between 0.0 and 2.0 inclusive

	return static_cast<float>(rand() / (static_cast<float>(RAND_MAX/2.0)));
}