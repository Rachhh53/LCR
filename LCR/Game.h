#pragma once

#include "Player.h"
#include "RollDice.h"
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

class Game {
private:
	Player m_player;
	Player NumberPlayers;
	//create a player instance
	Player player;
	//create a roll instance
	RollDice roll;


	//keep player names with their scores
	struct PlayerScores {
		std::string PlayerName;
		int PlayerChips = 0;
	};
	//store struct in vector so we can iterate through
	vector<PlayerScores> players;

	unsigned int rightPlayer = 0;
	unsigned int leftPlayer = 0;

	void WelcomePlayer();
	void GetPlayers();
	bool CheckPlayerStatus();
	void MoveChips(unsigned int moveChips);

	// variable to store which players turn it is
	unsigned int playerTurn = 0;
	unsigned int NextTurn() {
		//size less by 1 because center is counted here and we don't want to go out of range
		if (playerTurn == players.size() - 1) {
			//skip 0 because center doesn't roll
			playerTurn = 1;
		}
		else { //rotate turn to next player
			playerTurn = playerTurn + 1;
		}
		return playerTurn;
	}

	void DisplayPlayers() {
		string space1 = "             ";
		string space2 = "             ";
		string space3 = "             ";

		// if it is the last numbered players turn, we must go back to player one for right player
		if (playerTurn == players.size() - 1) {
			rightPlayer = 1;
		}
		else {
			rightPlayer = playerTurn + 1;
		}
		// if it is the first numbered players turn, we must get the last nubered player for the left player

		if (playerTurn == 1) {
			leftPlayer = players.size() - 1;
		}
		else {
			leftPlayer = playerTurn - 1;
		}
		// give a visual on where the players are in relation to each other
		cout << "	   __,__	               __,__		   	    __,__			" << endl;
		cout << "  .--.  .-\"     \"-.  .--.     .--.  .-\"     \"-.  .--.      .--.  .-\"     \"-.  .--.			" << endl;
		cout << " / .. \\/  .-. .-.  \\/ .. \\   / .. \\/  .-. .-.  \\/ .. \\    / .. \\/  .-. .-.  \\/ .. \\		" << endl;
		cout << "| |  '|  /   Y   \\  |'  | | | |  '|  /   Y   \\  |'  | |  | |  '|  /   Y   \\  |'  | |		" << endl;
		cout << "| \\   \\  \\ 0 | 0 /  /   / | | \\   \\  \\ 0 | 0 /  /   / |  | \\   \\  \\ 0 | 0 /  /   / |		" << endl;
		cout << " \\ '- ,\\.-\"`` ``\"-./, -' /   \\ '- ,\\.-\"`` ``\"-./, -' /    \\ '- ,\\.-\"`` ``\"-./, -' /		" << endl;
		cout << "  `'-' /_   ^ ^   _\\ '-'`     `'-' /_   ^ ^   _\\ '-'`      `'-' /_   ^ ^   _\\ '-'`			" << endl;
		cout << "      |  \\._   _./  |             |  \\._   _./  |              |  \\._   _./  |				" << endl;
		cout << "      \\   \\ `~` /   /             \\   \\ `~` /   /              \\   \\ `~` /   /				" << endl;
		cout << "       '._ '-=-' _.'               '._ '-=-' _.'                '._ '-=-' _.'				" << endl;
		cout << "          '~---~'                     '~---~'                      '~---~' 				" << endl;
		
		// tell the players who is where
		cout << "Left player: " << players.at(leftPlayer).PlayerName << endl;
		cout << "Chips: " << players.at(leftPlayer).PlayerChips << endl;
		cout << endl;
		cout << "Right player: " << players.at(rightPlayer).PlayerName << endl;
		cout << "Chips: " << players.at(rightPlayer).PlayerChips << endl;
		cout << endl;

		return;
	}

public:
	void RunGame();



};
