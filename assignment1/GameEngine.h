//need to make destructor and copy constructor
//need to add comments :P

#pragma once
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

class GameState {
public:
	GameState();
	void start();
	void mapLoaded();
	void mapValidated();
	void playersAdded();
	void assignReinforcement();
	void issueOrders();
	void executeOrders();
	void win();

	void setGameState(string _gameState);
	string getGameState();
private:
	string gameState;
};

class GameEngine {
	public:
		GameEngine();
		void loadMap();
		void validateMap();						
		void addPlayer(int _players);
		void assignCountries();
		void issueOrder();
		void endIssueOrders();
		void execOrder();
		void endExecOrders();
		void win();
		void play();
		void end();

		GameState* getState();
		void setState(GameState* _state);
		
		int getPlayers();
		void setPlayers(int _players);

		string getCommand();
		void setCommand(string _command);
		
	private:
		GameState* state;
		string command;
		int players;
};