#include "GameEngine.h"

//GameState default constructor
GameState::GameState()
{
	//set the game state to the first state
	gameState = "start";
}

//GameState copy constructor
GameState::GameState(const GameState& _GameState)
{
	//deep copying the gameState of _GameState
	gameState = string(_GameState.gameState);
}

//output stream operator for GameState
ostream& operator<<(ostream& out, const GameState& _GameState)
{
	return out << "Current state: " << _GameState.gameState << "\n---------------------" << endl;
}

//GameState deconstructor
GameState::~GameState()
{

}

//start state
void GameState::start()
{

}

//map loaded state
void GameState::mapLoaded()
{

}

//map validate state
void GameState::mapValidated()
{

}

//players added state
void GameState::playersAdded()
{

}

//assign reinforcement state
void GameState::assignReinforcement()
{

}

//issue orders state
void GameState::issueOrders()
{

}

//execute orders state
void GameState::executeOrders()
{

}

//win state
void GameState::win()
{

}

//gameState mutator
void GameState::setGameState(string _gameState) //need to make this a deep copy
{
	gameState = _gameState;
}

//gameState accessor
string GameState::getGameState() {
	return gameState;
}

//GameState assignment operator (shallow copy)
GameState& GameState::operator=(const GameState& _GameState) {
	gameState = _GameState.gameState;
	return *this;
}

//================================================================================================================================

//GameEngine default constructor
GameEngine::GameEngine() {
	state = nullptr;
}

//GameEngine parametrized constructor
GameEngine::GameEngine(GameState* _GameState, vector<Player*> _players) {
	state = _GameState;
	players = _players;
}

GameEngine::GameEngine(GameState* _GameState) {
	state = _GameState;
}

//GameEngine copy constructor
GameEngine::GameEngine(const GameEngine& _GameEngine)
{
	*state = *_GameEngine.state;
	players = _GameEngine.players;
}

//GameEngine destructor
GameEngine::~GameEngine() {
	state = nullptr;
}

void GameEngine::StringTolog() {
	ofstream output;
	output.open("C:\\Users\\aitan\\Documents\\visual studio workspace\\A2\\log.txt", ios::app);
	if (output.is_open()) {
		output << *this << endl;
		output << *this->state << endl;
		output.close();
	}
	else {
		cerr << "unable to open output file" << endl;
	}
}

void GameEngine::startTournament(vector<string> mapsName, vector<string> stratNames, int games, int turns)
{

    string winners[mapsName.size()][games];    // 2D array stores the winner's name for each game

    cout << "Starting tournament..." << endl;

	MapLoader mapLoader;
	vector<Map*> maps;

	//loading the maps
	for (int i = 0; i < mapsName.size(); i++)
	{
		mapLoader = MapLoader(mapsName[i]);
		//check if the file is valid to be a map
		if (mapLoader.fileChecker())
		{ 
			// load the map
			Map* map = new Map();
			map->mapLoad(mapLoader.getFileName());
			maps.push_back(map);
		}
		else
		{
			cout << "Invalid file" << endl;
			exit(0);
		}
	}
	
	//validating the maps
	for (int i = 0; i < mapsName.size(); i++)
	{
		//check if the map is valide
		if (maps[i]->Validate())
		{
			//if valid do nothing
		}
		else //if not valid print error and exit
		{
			cout << "Map invalid" << endl;
			exit(0);
		}
	}

    vector<PlayerStrategy*> strategies;

    // Add players to game and assign strategies
    for (int i = 0; i < stratNames.size(); i++){

        // Just naming the player after their strategy for simplicity
        this->addPlayer(stratNames[i], i);

        PlayerStrategy* thisStrategy;

        if (stratNames[i] == "aggressive")
            thisStrategy = new AggressivePlayerStrategy();
        else if (stratNames[i] == "benevolent")
            thisStrategy = new BenevolentPlayerStrategy();
        else if (stratNames[i] == "neutral")
            thisStrategy = new NeutralPlayerStrategy();
        else if (stratNames[i] == "cheater")
            thisStrategy = new CheaterPlayerStrategy();

        strategies.push_back(thisStrategy);

    }

    // Tournament loop
    // Outer loop for each map
    for (int m = 0; m < maps.size(); m++){

        // Loop for each game of the specified map
        for (int g = 0; g < games; g++) {

            // Start game
            this->gameStart(*maps[m]);

            // Inner loop for each turn
            for (int t = 0; t < turns; t++) {

                Player *currentPlayer = this->players[t % this->players.size()];    // Current player whose turn it is
                PlayerStrategy *currentStrategy = strategies[t % strategies.size()];    // Current player strategy...

                // First, deployment phase occurs
                currentStrategy->issueOrder(currentPlayer, "deploy");

                // Attack/transfer phase, specific action is randomized
                const int size = 5;
                string possibleActions[size] = {"advance", "bomb", "blockade", "airlift",
                                                "negotiate"};
                int actionIndex = (rand() % size) - 1;
                currentStrategy->issueOrder(currentPlayer, possibleActions[actionIndex]);

            }

            // If turn loop completes w/o a winner, force a draw.
            if (state->getGameState() != "win") {
                state->setGameState("win");
                state->win();
                winners[m][g] = "Draw";
                cout << "Draw occurred - Turn limit reached" << endl;
            }
        }
    }

     cout << "Tournament Ended" << endl;

    // Mem. management

    for(vector<Map*>::iterator i = maps.begin(); i != maps.end(); ++i ){
        delete *i;
    }

    for(vector<PlayerStrategy*>::iterator i = strategies.begin(); i != strategies.end(); ++i ){
        delete *i;
    }

}


//command responsible to load the map into the game
void GameEngine::loadMap(MapLoader mapLoader, Map &map) {
	//if the user enters this command while not being in the 'start' or 'mapLoaded' state, this command will not be executed and will result in an error
	if (state->getGameState() == "start" || state->getGameState() == "mapLoaded")
	{
		// if file is valid, load map
		if (mapLoader.fileChecker())
		{
			// load the map
			map.mapLoad(mapLoader.getFileName());
			//set the game state to the 'mapLoaded' state
			state->setGameState("mapLoaded");
			state->mapLoaded();
			cout << "Map Loaded Successfully" << endl;
			Notify(this);
		}
		else
		{
			cout << "Invalid file" << endl;
			return;
		}
	}
	else
	{
		cout << "Error: cannot perform this command\nPlease choose one of the available commands\n" << endl;
	}
}

//command responsible to validate the map of the game
void GameEngine::validateMap(Map &map) {
	//if the user enters this command while not being in the 'mapLoaded' state, this command will not be executed and will result in an error
	if (state->getGameState() == "mapLoaded")
	{
	
			//set the game state to the 'mapValidated' state
			state->setGameState("mapValidated");
			state->mapValidated();
			cout << "Map Validated Successfully" << endl;
		
		
	}
	else
	{
		cout << "Error: cannot perform this command\nPlease choose one of the available commands\n" << endl;
	}
}

//command responsible to enter the number of players in the game
void GameEngine::addPlayer(string playerName, int playerID) {
	//if the user enters this command while not being in the 'mapValidated' or 'playersAdded' state, this command will not be executed and will result in an error
	if (state->getGameState() == "mapValidated" || state->getGameState() == "playersAdded")
	{
		Player* p = new Player();
		p->setPlayerID(playerID);
		p->setPlayerName(playerName);
		this->players.push_back(p);

		//set the game state to the 'playersAdded' state
		state->setGameState("playersAdded");
		state->playersAdded();
		cout << "Player Added Successfully\nNumber of players: " << playerID << endl;
	}
	else
	{
		cout << "Error: cannot perform this command\nPlease choose one of the available commands\n" << endl;
	}
}

//command responsible to assign countries
void GameEngine::gameStart(Map& map) {
	//if the user enters this command while not being in the 'playersAdded' state, this command will not be executed and will result in an error
	if (state->getGameState() == "playersAdded")
	{
		int countriesOwned = map.getTerritories().size() * 0.1 * this->getPlayers().size();
		int countriesPerPlayer = countriesOwned / this->getPlayers().size();

		srand(time(nullptr));
		int random = rand() % map.getTerritories().size();

		//randomly assign territories to players
		for (int i = 0; i < this->getPlayers().size(); i++)
		{
			for (int j = 0; j < countriesPerPlayer ; j++)
			{
				while (true)
				{
					if (map.getTerritories()[random]->getPlayer() == nullptr)
					{
						this->getPlayers()[i]->addPlayerTerritory(map.getTerritories()[random]);
						map.getTerritories()[random]->setPlayer(this->getPlayers()[i]);
						break;
					}
					else if (map.getTerritories()[random]->getPlayer() != nullptr)
					{
						random = rand() % map.getTerritories().size();
					}
				}	
			}
			//assign 50 armies to each player
			this->getPlayers()[i]->setReinforcementPool(50);
		}
		cout << "number of countries per player: " << countriesPerPlayer << endl;
		

		vector<Player*> playerTemp;
		vector<Player*> playerTurn;
		

		for (int i = 0; i < this->getPlayers().size(); i++)
		{
			playerTemp.push_back(this->getPlayers()[i]);
		}

		for (int i = 0; i < this->getPlayers().size(); i++)
		{
			random = rand() % playerTemp.size();
			playerTurn.push_back(playerTemp[random]);
			playerTemp.erase(playerTemp.begin() + random);
		}

		cout << "Order: ";

		for (int i = 0; i < this->getPlayers().size(); i++)
		{
			this->setPlayers(playerTurn);
			cout << playerTurn[i]->getPlayerName() << " ";
		}

		cout << endl;

		//set the game state to the 'assignReinforcement' state
		state->setGameState("assignReinforcement");
		state->assignReinforcement();
		cout << "Countries assigned Successfully" << endl;
	}
	else
	{
		cout << "Error: cannot perform this command\nPlease choose one of the available commands\n" << endl;
	}
}

//command responsible to issue player order
void GameEngine::issueOrder()
{
	//if the user enters this command while not being in the 'assignReinforcement' or 'issueOrders' state, this command will not be executed and will result in an error
	if (state->getGameState() == "assignReinforcement" || state->getGameState() == "issueOrders")
	{
		//set the game state to the 'issueOrders' state
		state->setGameState("issueOrders");
		state->issueOrders();
		cout << "Orders Issued Successfully" << endl;
	}
	else
	{
		cout << "Error: cannot perform this command\nPlease choose one of the available commands\n" << endl;
	}
}

//command responsible to end player issuing order
void GameEngine::endIssueOrders()
{
	//if the user enters this command while not being in the 'issueOrders' state, this command will not be executed and will result in an error
	if (state->getGameState() == "issueOrders")
	{
		//set the game state to the 'executeOrders' state
		state->setGameState("executeOrders");
		state->executeOrders();
		cout << "Ended Issuing Orders Successfully" << endl;
	}
	else
	{
		cout << "Error: cannot perform this command\nPlease choose one of the available commands\n" << endl;
	}
}

//command responsible to execute the issued orders
void GameEngine::execOrder()
{
	//if the user enters this command while not being in the 'executeOrders' state, this command will not be executed and will result in an error
	if (state->getGameState() == "executeOrders")
	{
		//set the game state to the 'executeOrders' state
		state->setGameState("executeOrders");
		state->executeOrders();
		cout << "Executed orders Successfully" << endl;
	}
	else
	{
		cout << "Error: cannot perform this command\nPlease choose one of the available commands\n" << endl;
	}
}

//command responsible to end execution of orders
void GameEngine::endExecOrders()
{
	//if the user enters this command while not being in the 'executeOrders' state, this command will not be executed and will result in an error
	if (state->getGameState() == "executeOrders")
	{
		//set the game state to the 'assignReinforcement' state
		state->setGameState("assignReinforcement");
		state->assignReinforcement();
		cout << "Ended Executing Orders Successfully" << endl;
	}
	else
	{
		cout << "Error: cannot perform this command\nPlease choose one of the available commands\n" << endl;
	}
}

//command responsible to declaring the winner of the game 
void GameEngine::win()
{
	//if the user enters this command while not being in the 'executeOrders' state, this command will not be executed and will result in an error
	if (state->getGameState() == "executeOrders")
	{
		//set the game state to the 'win' state
		state->setGameState("win");
		state->win();
		cout << "Congratulations!!! You WON the warzon game!!!" << endl;
	}
	else
	{
		cout << "Error: cannot perform this command\nPlease choose one of the available commands\n" << endl;
	}
}

//command responsible to start a new game
void GameEngine::play()
{
	//if the user enters this command while not being in the 'win' state, this command will not be executed and will result in an error
	if (state->getGameState() == "win")
	{
		//set the game state to the 'start' state and start a new game
		state->setGameState("start");
		state->start();
		cout << "Starting New Game...\nWelcome to Warzone!!!\n" << endl;
	}
	else
	{
		cout << "Error: cannot perform this command\nPlease choose one of the available commands\n" << endl;
	}
}

//command responsible to terminate the program
void GameEngine::end()
{
	//if the user enters this command while not being in the 'win' state, this command will not be executed and will result in an error
	if (state->getGameState() == "win")
	{
		//end program
		cout << "Thank you for playing\n\nProgram terminated" << endl;
	}
	else
	{
		cout << "Error: cannot perform this command\nPlease choose one of the available commands\n" << endl;
	}
}

//state mutator
void GameEngine::setState(GameState* _state)
{
	state = _state;
}

//state accessor
GameState* GameEngine::getState()
{
	return state;
}

void GameEngine::setPlayers(vector<Player*> _players)
{
	this->players = _players;
}

//players accessor
vector<Player*> GameEngine::getPlayers()
{
	return this->players;
}

//output stream operator for GameEngine
ostream& operator<<(ostream& out, const GameEngine& _GameEngine) {
	//print current state
	cout << *_GameEngine.state;

	cout << "Available commands : " << endl;
	//print the available commands depending on the state of the program
	if (_GameEngine.state->getGameState() == "start")
	{
		return out << " - load map" << endl;
	}
	else if (_GameEngine.state->getGameState() == "mapLoaded")
	{
		return out << " - load map\n - validate map" << endl;
	}
	else if (_GameEngine.state->getGameState() == "mapValidated")
	{
		return out << " - add player" << endl;
	}
	else if (_GameEngine.state->getGameState() == "playersAdded")
	{
		return out << " - add player\n - game start" << endl;
	}
	else if (_GameEngine.state->getGameState() == "assignReinforcement")
	{
		return out << " - issue order" << endl;
	}
	else if (_GameEngine.state->getGameState() == "issueOrders")
	{
		return out << " - issue order\n - end issue orders" << endl;
	}
	else if (_GameEngine.state->getGameState() == "executeOrders")
	{
		return out << " - execute order\n - end execute orders\n - win" << endl;
	}
	else if (_GameEngine.state->getGameState() == "win")
	{
		return out << " - play\n - end" << endl;
	}
	
}

//GameEngine assignment operator (shallow copy)
GameEngine& GameEngine::operator=(const GameEngine& _GameEngine) {
	state = _GameEngine.state;
	players = _GameEngine.players;
	return *this;
}

// Reinforcement Phase
//void GameEngine::reinforcementPhase(vector<Player*> players, Map* map)
//{
//
//	// get all territories of a map
//	vector<Territory*> T = map->getTerritories();
//	vector<Territory*> c1, c2, c3, c4;
//
//	// group territories of a continent together
//	for (int i = 0; i < T.size(); i++)
//	{
//		if (T[i]->getContinent() == 1) {
//			c1.push_back(T[i]);
//		}
//		else if (T[i]->getContinent() == 2) {
//			c2.push_back(T[i]);
//		}
//		else if (T[i]->getContinent() == 3) {
//			c3.push_back(T[i]);
//		}
//		else if (T[i]->getContinent() == 4) {
//			c4.push_back(T[i]);
//		}
//	}
//
//	// Loop through all players in a game
//	for (int i = 0; i < players.size(); i++)
//	{
//		int reinforcement = floor(players[i]->getTerritories().size() / 3); // get allowed reinforcement value of player
//
//		// check if players[i] controls a certain continent
//		bool c1Bonus = players[i]->ContinentBonus(c1);
//		bool c2Bonus = players[i]->ContinentBonus(c2);
//		bool c3Bonus = players[i]->ContinentBonus(c3);
//		bool c4Bonus = players[i]->ContinentBonus(c4);
//
//		// assign bonus to player's reinforcement
//		if (c1Bonus && (players[i] == c1[0]->getPlayer())) {
//			reinforcement += 2;
//		}
//		else if (c2Bonus && (players[i] == c2[0]->getPlayer())) {
//			reinforcement += 2;
//		}
//		else if (c3Bonus && (players[i] == c3[0]->getPlayer())) {
//			reinforcement += 2;
//		}
//		else if (c4Bonus && (players[i] == c4[0]->getPlayer())) {
//			reinforcement += 2;
//		}
//
//		if (reinforcement < 3)
//		{
//			players[i]->setReinforcementPool(players[i]->getReinforcementPool() + 3); // minimum reinforcement value of 3
//		}
//		else {
//			players[i]->setReinforcementPool(players[i]->getReinforcementPool() + reinforcement); // set new reinforcement value allocated to player
//		}
//	}
//}
//
//// Order Issuing Phase
//void GameEngine::issueOrdersPhase(vector<Player*> players)
//{
//	for (int i = 0; i < players.size(); i++)
//	{
//		players[i]->issueOrder(players[i]->getTerritories());
//	}
//}
//
//// Order Execution Phase
//void GameEngine::executeOrdersPhase()
//{
//	vector<Order*> orderList;
//
//}
//
//// Main Game Loop
//void GameEngine::mainGameLoop(vector<Player*> players, Map* map)
//{
//
//	// loop until someone wins the game
//	while (state->getGameState() != "win")
//	{
//
//		for (int i = 0; i < players.size(); i++) {
//
//			// Check if a player is eliminated
//			if (players[i]->getTerritories().empty()) {
//				players.erase(players.begin() + i);
//			}
//
//			// Check if game has been won
//			if (players.size() == 1) {
//				win();
//				cout << "Player" << players[i]->getPiD() << "won the game!" << endl;
//			}
//
//		}
//
//		reinforcementPhase(players, map); // reinforcement phase
//
//		issueOrder();
//		issueOrdersPhase(players); // issue orders phase
//		endIssueOrders();
//
//		executeOrdersPhase(); // execute orders phase
//		endExecOrders();
//	}
//}