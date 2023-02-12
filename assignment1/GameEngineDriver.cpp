#include "GameEngine.h"

int main()
{
	GameEngine game = GameEngine();
	GameState s = GameState();
	game.setState(&s);
	string command = "play";
	int playersCount = 0;

	cout << "welcome to warzone!!!\n" << endl;

	while (true)
	{
		cout << "Current state: " << game.getState()->getGameState() << "\n---------------------\nAvailable commands:" << endl;

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

		cout << "Enter a command: ";
		getline(cin, command);
		cout << endl;
		transform(command.begin(), command.end(), command.begin(), ::tolower);

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
				cout << "Enter the number of players (2-6 players): " << endl;
				cin >> playersCount;

				cin.clear();
				cin.ignore(numeric_limits<int>::max(), '\n');

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
		else if (command == "end")
		{
			game.end();
		}
		else
		{
			cout << "ERROR: command '" << command << "' does not exist\nPlease choose one of the available commands\n" << endl;
		}
		cout << "========================================" << endl;
	}
	return 0;
}