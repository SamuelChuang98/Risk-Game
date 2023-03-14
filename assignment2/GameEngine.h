#pragma once
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

namespace GameEngineSpace {
	int GameEngineMain();
}

//GameState is a class responsible for the state of the game
class GameState {
public:
	GameState(); //default constructor
	~GameState();	//destructor
	GameState(const GameState& _GameState);	//copy constructor

	//each method of these 8 methods represent a state in the game
	//each one of them run based on the data member "gameState"
	void start();				//start state
	void mapLoaded();			//map loaded state
	void mapValidated();		//map validate state
	void playersAdded();		//players added state
	void assignReinforcement();	//assign reinforcement state
	void issueOrders();			//issue orders state
	void executeOrders();		//execute orders state
	void win();					//win state

	//gameState mutator
	void setGameState(string _gameState);
	//gameState acessor
	string getGameState();

	friend ostream& operator<<(ostream& out, const GameState& _GameState); //output stream operator
	GameState& operator=(const GameState& _GameState);	//equal operator
private:
	//responsable for deciding the state of the game
	string gameState;
};

//GameEngine class responsible for the transition of the game from a state to another
class GameEngine {
public:
	GameEngine();	//default constructor
	GameEngine(const GameEngine& _gameEngine);	//copy constructor
	GameEngine(GameState* _GameState, int _players);	//parametrised constructor
	~GameEngine();	//deconstructor

	//each method of these 11 methods is an executable command when the game engine is running
	//each of these commands is responsible to transition the game from a state to another
	void loadMap();					//transition from 'start' state to 'map loaded' state
	void validateMap();				//transition from 'map loaded' state to 'map validated' state
	void addPlayer(int _players);	//transition from 'map validated' state to 'players added' state
	void assignCountries();			//transition from 'players added' state to 'assign reinforcement' state
	void issueOrder();				//transition from 'assign reinforcement' state to 'issue order' state
	void endIssueOrders();			//transition from 'issue order' state to 'execute orders' state
	void execOrder();				//transition from 'execute orders' state to 'execute orders' state
	void endExecOrders();			//transition from 'execute orders' state to 'assign reinforcement' state
	void win();						//transition from 'execute orders' state to 'win' state
	void play();					//transition from 'win' state to 'start' state
	void end();						//exit 'win' state and terminates the program

	//state accessor
	GameState* getState();
	//state mutator
	void setState(GameState* _state);

	//players accessor
	int getPlayers();
	//players mutator
	void setPlayers(int _players);

	friend ostream& operator<<(ostream& out, const GameEngine& _GameEngine);	//output stream operator
	GameEngine& operator=(const GameEngine& _GameEngine);	//GameEngine assign operator

private:
	//pointer to the state object
	GameState* state;
	//number of players in the game
	int players;
};