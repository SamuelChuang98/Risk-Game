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

//command responsible to load the map into the game
void GameEngine::loadMap(MapLoader mapLoader, Map map) {
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
		}
	}
	else
	{
		cout << "Error: cannot perform this command\nPlease choose one of the available commands\n" << endl;
	}
}

//command responsible to validate the map of the game
void GameEngine::validateMap(Map map) {
	//if the user enters this command while not being in the 'mapLoaded' state, this command will not be executed and will result in an error
	if (state->getGameState() == "mapLoaded")
	{
		if (map.Validate())
		{
			//set the game state to the 'mapValidated' state
			state->setGameState("mapValidated");
			state->mapValidated();
			cout << "Map Validated Successfully" << endl;
		}
		
	}
	else
	{
		cout << "Error: cannot perform this command\nPlease choose one of the available commands\n" << endl;
	}
}

//command responsible to enter the number of players in the game
void GameEngine::addPlayer(int _players) {
	//if the user enters this command while not being in the 'mapValidated' or 'playersAdded' state, this command will not be executed and will result in an error
	if (state->getGameState() == "mapValidated" || state->getGameState() == "playersAdded")
	{
		Player* p = new Player();

		//set the number of players in the game
		for (int i = 0; i < _players; i++) {
			p->setPlayerID(i + 1);
			p->setReinforcementPool(50);
			this->players.push_back(p);
		}
		delete p;
		p = nullptr;

		//set the game state to the 'playersAdded' state
		state->setGameState("playersAdded");
		state->playersAdded();
		cout << "Players Added Successfully" << endl;
	}
	else
	{
		cout << "Error: cannot perform this command\nPlease choose one of the available commands\n" << endl;
	}
}

//command responsible to assign countries
void GameEngine::gameStart() {
	//if the user enters this command while not being in the 'playersAdded' state, this command will not be executed and will result in an error
	if (state->getGameState() == "playersAdded")
	{
		
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
		return out << " - add player\n - assign countries" << endl;
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
void GameEngine::reinforcementPhase(vector<Player*> players)
{
	// Loop through all players in a game
	for (int i = 0; i < players.size(); i++)
	{
		int reinforcement = floor(players[i]->getTerritories().size() / 3); // get allowed reinforcement value of player

		// check for continent bonus
		/*
		INSERT CODE HERE
		*/
		vector<Territory*> ter_list = players[i]->getTerritories();

		if (reinforcement < 3)
		{
			players[i]->setReinforcementPool(players[i]->getReinforcementPool() + 3); // minimum reinforcement value of 3
		}
		else {
			players[i]->setReinforcementPool(players[i]->getReinforcementPool() + reinforcement); // set new reinforcement value allocated to player
		}
	}
}

// Order Issuing Phase
void GameEngine::issueOrdersPhase(vector<Player*> players)
{
	for (int i = 0; i < players.size(); i++)
	{
		players[i]->issueOrder(players[i]->getTerritories());
	}
}

// Order Execution Phase
void GameEngine::executeOrdersPhase()
{
	vector<Order*> orderList;

}

// Main Game Loop
void GameEngine::mainGameLoop(vector<Player*> players)
{

	while (state->getGameState() != "win")
	{

		for (int i = 0; i < players.size(); i++) {

			// Check if a player is eliminated
			if (players[i]->getTerritories().empty()) {
				players.erase(players.begin() + i);
			}

			// Check if game has been won
			if (players.size() == 1) {
				win();
				cout << "Player" << players[i]->getPlayerID() << "won the game!" << endl;
			}

		}

		reinforcementPhase(players); // reinforcement phase
		
		issueOrder();
		issueOrdersPhase(players); // issue orders phase
		endIssueOrders();

		executeOrdersPhase(); // execute orders phase
		endExecOrders();
	}
}