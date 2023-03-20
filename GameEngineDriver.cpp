#include "GameEngine.h"


int GameEngineSpace::GameEngineMain()
{
	GameState s = GameState();	//creating a game state object
	GameEngine game = GameEngine(&s);	//creating a GameEngine object with GameState pointing at GameState s
	string command = "play"; //command string that will be responsible to get the input from the user
	int playersCount = 0;	//number of players in the game
	Map map = Map();
	string filePath = "C:\\Users\\aitan\\Documents\\visual studio workspace\\A2\\", mapName = "";
	MapLoader mapLoader = MapLoader();
	Deck *deck = new Deck();
	//LogObserver* logObserver = new LogObserver();
	//game.Attach(logObserver);


	cout << "welcome to warzone!!!\n" << endl;

	//infinite loop responsible for running the game
	while (true)
	{
		//print all informations about the game
		cout << game;

		//ask the user to enter a command
		cout << "Enter a command: ";
		getline(cin, command);
		cout << endl;
		//convert the command to lower case
		transform(command.begin(), command.end(), command.begin(), ::tolower);

		//transition the state of the program depending on the command that the user entered
		//if the user entered a command that does not exist, the program will not transition and print an error and ask the user to enter a valid command
		if (command.find("load map") != std::string::npos || command.find("loadmap") != std::string::npos )
		{
			string temp = "";
			vector<string> tempVec;

			//break values into tempVec
			for (int i = 0; i < command.size(); i++) {
				if (command[i] == ' ')
				{
					tempVec.push_back(temp);
					temp = "";
				}
				else if (i == command.size() - 1)
				{
					temp = temp + command[i];
					tempVec.push_back(temp);
					temp = "";
				}
				else {
					temp = temp + command[i];
				}
			}
			for (int i = 0; i < tempVec.size(); i++)
			{
				if (tempVec[i] != "load" || tempVec[i] != "map" || tempVec[i] != "loadmap" || tempVec[i] != " " || tempVec[i] != "")
				{
					mapName = tempVec[tempVec.size()-1];
				}
			}
			mapLoader.setFileName(filePath + mapName + ".map");
			game.loadMap(mapLoader, map);
		}
		else if (command == "validate map" || command == "validatemap")
		{
			game.validateMap(map);
		}
		else if (command.find("addplayer") != std::string::npos || command.find("add player") != std::string::npos)
		{

			string temp = "";
			vector<string> tempVec;

			//break values into tempVec
			for (int i = 0; i < command.size(); i++) {
				if (command[i] == ' ')
				{
					tempVec.push_back(temp);
					temp = "";
				}
				else if (i == command.size() - 1)
				{
					temp = temp + command[i];
					tempVec.push_back(temp);
					temp = "";
				}
				else 
				{
					temp = temp + command[i];
				}
			}

			playersCount += 1;
			game.addPlayer(tempVec[tempVec.size() -1], playersCount);

		}
		else if (command == "game start" || command == "gamestart")
		{
			if (playersCount > 1 && playersCount < 7)
			{
				game.gameStart(map);
			}
			else if (playersCount > 6)
			{
				cout << "there can be at most 6 players" << endl;
			}
			else if (playersCount < 2)
			{
				cout << "there must be at least 2 players" << endl;
			}
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
	}
	return 0;
}

int main()
{
	GameEngineSpace::GameEngineMain();
}


