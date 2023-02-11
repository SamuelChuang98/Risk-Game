#include "GameEngine.h"

GameState::GameState()
{
	gameState = "start";
}

void GameState::start()
{
	
}

void GameState::mapLoaded()
{

}

void GameState::mapValidated()
{

}

void GameState::playersAdded()
{

}

void GameState::assignReinforcement()
{

}

void GameState::issueOrders()
{

}

void GameState::executeOrders()
{

}

void GameState::win()
{

}

void GameState::setGameState(string _gameState) //need to make this a deep copy
{
	gameState = _gameState;
}

string GameState::getGameState()
{
	return gameState;
}

//================================================================================================================================

GameEngine::GameEngine() {	//defining default constructor
	state = nullptr;
	players = 0;
}

void GameEngine::loadMap() {
	cout << state->getGameState();
	if (state->getGameState() == "start" || state->getGameState() == "mapLoaded")
	{
		state->setGameState("mapLoaded");
		state->mapLoaded();
	}
	else
	{
		cout << "Error: cannot perform this command\nPlease choose one of the available commands\n" << endl;
	}
}

void GameEngine::validateMap() {
	if (state->getGameState() == "mapLoaded")
	{
		state->setGameState("mapValidated");
		state->mapValidated();
	}
	else
	{
		cout << "Error: cannot perform this command\nPlease choose one of the available commands\n" << endl;
	}
}

void GameEngine::addPlayer(int _players) {
	if (state->getGameState() == "mapValidated" || state->getGameState() == "playersAdded")
	{
		players = _players;
		state->setGameState("playersAdded");
		state->playersAdded();
	}
	else
	{
		cout << "Error: cannot perform this command\nPlease choose one of the available commands\n" << endl;
	}
}

void GameEngine::assignCountries() {
	if (state->getGameState() == "playersAdded")
	{
		state->setGameState("assignReinforcement");
		state->assignReinforcement();
	}
	else
	{
		cout << "Error: cannot perform this command\nPlease choose one of the available commands\n" << endl;
	}
}

void GameEngine::issueOrder()
{
	if (state->getGameState() == "assignReinforcement" || state->getGameState() == "issueOrders")
	{
		state->setGameState("issueOrders");
		state->issueOrders();
	}
	else
	{
		cout << "Error: cannot perform this command\nPlease choose one of the available commands\n" << endl;
	}
}

void GameEngine::endIssueOrders()
{
	if (state->getGameState() == "issueOrders")
	{
		state->setGameState("executeOrders");
		state->executeOrders();
	}
	else
	{
		cout << "Error: cannot perform this command\nPlease choose one of the available commands\n" << endl;
	}
}

void GameEngine::execOrder()
{
	if (state->getGameState() == "executeOrders")
	{
		state->setGameState("executeOrders");
		state->executeOrders();
	}
	else
	{
		cout << "Error: cannot perform this command\nPlease choose one of the available commands\n" << endl;
	}
}

void GameEngine::endExecOrders()
{
	if (state->getGameState() == "executeOrders")
	{
		state->setGameState("assignReinforcement");
		state->assignReinforcement();
	}
	else
	{
		cout << "Error: cannot perform this command\nPlease choose one of the available commands\n" << endl;
	}
}

void GameEngine::win()
{
	if (state->getGameState() == "executeOrders")
	{
		state->setGameState("win");
		state->win();
	}
	else
	{
		cout << "Error: cannot perform this command\nPlease choose one of the available commands\n" << endl;
	}
}

void GameEngine::play()
{
	if (state->getGameState() == "win")
	{
		//start a new game
		state->setGameState("start");
		state->start();
	}
	else
	{
		cout << "Error: cannot perform this command\nPlease choose one of the available commands\n" << endl;
	}
}

void GameEngine::end()
{
	if (state->getGameState() == "win")
	{
		//end program
		exit(1);
	}
	else
	{
		cout << "Error: cannot perform this command\nPlease choose one of the available commands\n" << endl;
	}
}

void GameEngine::setState(GameState* _state)
{
	state = _state;
}

GameState* GameEngine::getState()
{
	return state;
}

int GameEngine::getPlayers()
{
	return players;
}
