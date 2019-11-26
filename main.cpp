#include <iostream>
#include <string>
#include <ctime>
#include "Point2D.h"
#include "Vector2D.h"
#include "GameObject.h"
#include "Building.h"
#include "PokemonCenter.h"
#include "PokemonGym.h"
#include "Pokemon.h"
#include "Model.h"
#include "GameCommand.h"
#include "View.h"
using namespace std;

int main()
{
	// Seed random number generator (for get random money functions)
	srand(time(NULL));
	// Initialize Model and inputs
	Model master_key = Model();
	View master_graph = View();
	// Start core gameplay loop
	master_key.ShowStatus();
	master_key.Display(master_graph);

	while(true) // Goes on until exit() is called somewhere within program
	{
		// Initialize input receivers
		char commandCode;
		int inputOne; // services ID, ID1
		int inputTwo; // services ID2
		int inputThree; // Services stamina_amoung and unit_amount
		double x;
		double y;
		// Prompt for input
		cout << "Enter command: ";
		cin >> commandCode;
		switch (commandCode)
		{
			case 'm':
				cin >> inputOne; // ID - Pokemon
				cin >> x;
				cin >> y;
				DoMoveCommand(master_key, inputOne, Point2D(x, y));
				break;
			case 'g':
				cin >> inputOne; // ID1 - Pokemon
				cin >> inputTwo; // ID2 - PokemonGym
				DoMoveToGymCommand(master_key, inputOne, inputTwo);
				break;
			case 'c':
				cin >> inputOne; // ID1 - Pokemon
				cin >> inputTwo; // ID2 - PokemonCenter
				DoMoveToCenterCommand(master_key, inputOne, inputTwo);
				break;
			case 's':
				cin >> inputOne; // ID - Pokemon
				DoStopCommand(master_key, inputOne);
				break;
			case 'r':
				cin >> inputOne; // ID1 - Pokemon
				// cin >> inputTwo; // ID2 - PokemonCenter; REDACTED
				cin >> inputThree; // stamina_amount
				DoRecoverInCenterCommand(master_key, inputOne, inputThree);
				break;
			case 't':
				cin >> inputOne; // ID1 - Pokemon
				// cin >> inputTwo; // ID2 - Pokemon Gym; REDACTED
				cin >> inputThree; // unit_amount
				DoTrainInGymCommand(master_key, inputOne, inputThree);
				break;
			case 'v':
				DoGoCommand(master_key, master_graph);
				break;
			case 'x':
				DoRunCommand(master_key, master_graph);
				break;
			case 'q':
				exit(0);
				break;
			}
			// Display map
			master_key.Display(master_graph);
			// Flush input between prompts
			cin.ignore(100, '\n');
	}

	return 0;
}