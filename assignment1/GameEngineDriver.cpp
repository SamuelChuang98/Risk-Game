#include "GameEngine.h"

int GameEngineSpace::GameEngineMain()
{
	GameState s = GameState();	//creating a game state object
	GameEngine game = GameEngine(&s, 0);	//creating a GameEngine object with GameState pointing at GameState s
	string command = "play"; //command string that will be responsible to get the input from the user
	int playersCount = 0;	//number of players in the game

	cout << "welcome to warzone!!!\n" << endl;

	//infinite loop responsible for running the game
	while (true)
	{
		//print current state of the program
		cout << "Current state: " << game.getState()->getGameState() << "\n---------------------\nAvailable commands:" << endl;

		//print the available commands depending on the state of the program
		if (game.getState()->getGameState() == "start")
		{
			cout << " - load map" << endl;
		}
		else if (game.getState()->getGameState() == "mapLoaded")
		{
			cout << " - load map\n - validate map" << endl;
		}
		else if (game.getState()->getGameState() == "mapValidated")
		{
			cout << " - add player" << endl;
		}
		else if (game.getState()->getGameState() == "playersAdded")
		{
			cout << " - add player\n - assign countries" << endl;
		}
		else if (game.getState()->getGameState() == "assignReinforcement")
		{
			cout << " - issue order" << endl;
		}
		else if (game.getState()->getGameState() == "issueOrders")
		{
			cout << " - issue order\n - end issue orders" << endl;
		}
		else if (game.getState()->getGameState() == "executeOrders")
		{
			cout << " - execute order\n - end execute orders\n - win" << endl;
		}
		else if (game.getState()->getGameState() == "win")
		{
			cout << " - play\n - end" << endl;
		}

		//ask the user to enter a command
		cout << "Enter a command: ";
		getline(cin, command);
		cout << endl;
		//convert the command to lower case
		transform(command.begin(), command.end(), command.begin(), ::tolower);

		//transition the state of the program depending on the command that the user entered
		//if the user entered a command that does not exist, the program will not transition and print an error and ask the user to enter a valid command
		if (command == "load map" || command == "loadmap")
		{
			game.loadMap();
		}
		else if (command == "validate map" || command == "validatemap")
		{
			game.validateMap();
		}
		else if (command == "add player" || command == "addplayer")
		{
			try {
				//ask the user to enter the number of players
				cout << "Enter the number of players (2-6 players): " << endl;
				cin >> playersCount;

				//clear the input buffer to allow the program to accept multiple inputs
				cin.clear();
				cin.ignore(numeric_limits<int>::max(), '\n');

				//print an error if the user enter an invalid number
				if (playersCount > 6 || playersCount < 2)
				{
					cout << "ERROR: please enter a valid number" << endl;
				}
				else
				{
					game.addPlayer(playersCount);
					
				}
			}
			catch (exception e)
			{
				cout << "ERROR: please enter a valid number" << endl;
			}
		}
		else if (command == "assign countries" || command == "assigncountries")
		{
			game.assignCountries();
		}
		else if (command == "issue order" || command == "issueorder")
		{
			game.issueOrder();
		}
		else if (command == "end issue orders" || command == "endissueorders")
		{
			game.endIssueOrders();
		}
		else if (command == "execute order" || command == "executeorder")
		{
			game.execOrder();
		}
		else if (command == "end execute orders" || command == "endexecuteorders")
		{
			game.endExecOrders();
		}
		else if (command == "win")
		{
			game.win();
		}
		else if (command == "play")
		{
			game.play();
		}
		else if (command == "end" && game.getState()->getGameState() == "win")
		{
			game.end();
			//break out of the infinite loop and terminate the program
			break;
		}
		else
		{
			cout << "ERROR: command '" << command << "' does not exist\nPlease choose one of the available commands\n" << endl;
		}
		cout << "========================================" << endl;
	}
	return 0;
}