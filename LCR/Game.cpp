#include "stdafx.h"
#include "Game.h"
#include "Rules.h"

void Game::WelcomePlayer()
{
	cout << "Welcome to" << endl << endl;
	// credit: http://patorjk.com/software/taag/#p=display&f=Big&t=Left%20Center%20Right
	cout << " _           __ _      _____           _              _____  _       _     _" << endl;
	cout << "| |         / _| |    / ____|         | |            |  __ \\(_)     | |   | |" << endl;
	cout << "| |     ___| |_| |_  | |     ___ _ __ | |_ ___ _ __  | |__) |_  __ _| |__ | |_" << endl;
	cout << "| |    / _ \\  _| __| | |    / _ \\ '_ \\| __/ _ \\ '__| |  _  /| |/ _` | '_ \\| __|" << endl;
	cout << "| |___|  __/ | | |_  | |___ | __/ | | | ||  __/ |    | | \\ \\| | (_| | | | | |_" << endl;
	cout << "|______\\___|_|  \\__|  \\_____\\___|_| |_|\\__\\___|_|    |_|  \\_\\_|\\__, |_| |_|\\__|" << endl;
	cout << "								_/  |" << endl;
	cout << "							       |___/" << endl;

	cout << "Make this window fill the screen for a better experience!" << endl;
	cout << endl;

	
	Rules::Rules();

	return;
}

void Game::GetPlayers() {
	// Number of players cannot be negative
	unsigned int NumPlayers = 0;

	// get number of players
	while (NumPlayers < 3) {
		cout << "Please enter number of players: ";
		cin >> NumPlayers;
		if (NumPlayers < 3) {
			cout << "Number of players must be greater than 3." << endl;
			cin.ignore();
		}
		else {
			NumberPlayers.SetNumPlayers(NumPlayers);
		}
	}

	cout << "Looks like there are " << NumberPlayers.GetNumPlayers() << " playing today!" << endl;

	//make the vector large enough to hold all the players and initalize index 0 to be the center
	players.resize(NumberPlayers.GetNumPlayers() + 1);
	players.at(0).PlayerName = "Center";
	players.at(0).PlayerChips = 0;

	// Get names of players and store in vector
	for (unsigned int i = 1; i <= NumberPlayers.GetNumPlayers(); ++i) {
		cout << "Please enter player " << i << "'s name" << endl;
		cin.ignore();
		//create an instance of player and store names and give every play 3 chips to begin
		PlayerScores player;
		string name;
		cin >> name;
		players.at(i).PlayerName = name;
		players.at(i).PlayerChips = 3;
		// greet each player by name and let them know they've started with 3 chips
		cout << endl << "Hello " << players.at(i).PlayerName << endl;
		cout << "You have " << players.at(i).PlayerChips << " chips" << endl;
		cout << endl;
	}

	return;
}

bool Game::CheckPlayerStatus() {
	unsigned int playersWithChips = 0;
	bool isWinner = false;
	// begin loop at 1 because 0 is center and center can't win
	for (unsigned int i = 1; i < Game::players.size(); ++i) {
		if (Game::players.at(i).PlayerChips != 0) {
			//count number of players with more than 0 chips
			playersWithChips = playersWithChips + 1;
		}
	}
	//keep playing while more than one player has chips
	if (playersWithChips > 1) {
		return false;
	}
	//if only one player has more than 0 chips, they are the winner
	else {
		return true;
	}
}

void Game::MoveChips(unsigned int moveChips) {
	switch (moveChips) {
	case 1:
		//move chips to the left
		players.at(playerTurn).PlayerChips = players.at(playerTurn).PlayerChips - 1;
		players.at(leftPlayer).PlayerChips = players.at(leftPlayer).PlayerChips + 1;
		cout << "You rolled a 1 so you pass a chip to the left player, " << players.at(leftPlayer).PlayerName << endl;
		return;
	case 2:
		//move chips to the right
		players.at(playerTurn).PlayerChips = players.at(playerTurn).PlayerChips - 1;
		players.at(rightPlayer).PlayerChips = players.at(rightPlayer).PlayerChips + 1;
		cout << "You rolled a 2 so you pass a chip to the right player, " << players.at(rightPlayer).PlayerName << endl;
		return;
	case 3:
		//move chips to the center
		players.at(playerTurn).PlayerChips = players.at(playerTurn).PlayerChips - 1;
		players.at(0).PlayerChips = players.at(0).PlayerChips + 1;
		cout << "You rolled a 3 so you pass a chip to the center. That chip is now out of play." << endl;
		return;
	case 4:
		cout << "You rolled a " << moveChips << " so nothing happens." << endl;
		return;
	case 5:
		cout << "You rolled a " << moveChips << " so nothing happens." << endl;
		return;
	case 6:
		cout << "You rolled a " << moveChips << " so nothing happens." << endl;
		return;
	}
}


void Game::RunGame()
{
	WelcomePlayer();
	GetPlayers();

	// check that variables from GetPlayers are stored
	cout << "There are " << Game::players.size() - 1 << " players playing" << endl;
	cout << endl;

	//set to false so the while loop executes at least once
	bool shouldEnd = false;
	while (shouldEnd == false)
	{	// change the active player
		unsigned int playersTurn;
		playersTurn = NextTurn(); // Game.h
		cout <<  players.at(playersTurn).PlayerName << ", you're the monkey in the middle!" << endl;
		cout << "You have: " << players.at(playersTurn).PlayerChips << " chips." << endl;

		// Assign number of dice the player gets to roll and display
		unsigned int numDice = 0;
		if (players.at(playersTurn).PlayerChips == 0) {
			numDice = 0;
			cout << "Sorry, you don't have any chips, so you can't roll any dice this turn." << endl;
		}
		else if (players.at(playersTurn).PlayerChips > 2) {
			numDice = 3;
			cout << "That means you get to roll 3 dice!" << endl;
		}
		else {
			numDice = players.at(playersTurn).PlayerChips;
			cout << "That means you get to roll " << players.at(playersTurn).PlayerChips << " dice!" << endl;
		}

		//display the left and right players
		if (players.at(playersTurn).PlayerChips != 0) {
			DisplayPlayers();


			//roll the appropriate number of dice and display results
			unsigned int moveChips = 0;
			while (numDice > 0) {
				moveChips = roll.Roll();
				MoveChips(moveChips);
				//decrease dice so the loop ends when we get to 0 and numDice is initalzied for next player
				--numDice;
				// Added a pause so the two dice rolls will not always be the same because the system runs so fast
				cout << "Press ENTER to continue..." << endl;
				cin.ignore();
				cin.get();
			}
			cout << "You now have " << players.at(playersTurn).PlayerChips << " chips." << endl;
			cout << endl;
		}
		//show scoreboard
		cout << "Here are the player standings: " << endl;
		unsigned int standings = 0;
		for (standings = 1; standings < players.size(); ++standings) {
			cout << players.at(standings).PlayerName << " has " << players.at(standings).PlayerChips << " chips." << endl;
			cout << endl;
		}

		// Added a pause so next player can be ready
		cout << "Press ENTER when the next player is ready..." << endl;
		cin.ignore();
		cin.get();

		//check for a winner
		shouldEnd = CheckPlayerStatus();
		/*shouldEnd = true;*/
	}
	// Output who the winner is
	unsigned int x;
	for (x = 1; x < Game::players.size(); ++x) {
		if (players.at(x).PlayerChips != 0) {
			cout << "   ____                            _         _       _   _                 _ " << endl;
			cout << "  / ___|___  _ __   __ _ _ __ __ _| |_ _   _| | __ _| |_(_) ___  _ __  ___| |" << endl;
			cout << " | |   / _ \\| '_ \\ / _` | '__/ _` | __| | | | |/ _` | __| |/ _ \\| '_ \\/ __| |" << endl;
			cout << " | |__| (_) | | | | (_| | | | (_| | |_| |_| | | (_| | |_| | (_) | | | \\__ \\_|" << endl;
			cout << "  \\____\\___/|_| |_|\\__, |_|  \\__,_|\\__|\\__,_|_|\\__,_|\\__|_|\\___/|_| |_|___(_)" << endl;
			cout << "                   |___/                                                     " << endl;
			cout << players.at(x).PlayerName <<", you have won the game!" << endl;
			// credit: https://www.asciiart.eu/holiday-and-events/fireworks
			// Art by Joan Stark
			cout << "                                   .''.          " << endl;
			cout << "       .''.      .        *''*    :_\\/_:     .   " << endl;
			cout << "      :_\\/_:   _\\(/_  .:.*_\\/_*   : /\\ :  .'.:.'." << endl;
			cout << "  .''.: /\\ :   ./)\\   ':'* /\\ * :  '..'.  -=:o:=-" << endl;
			cout << " :_\\/_:'.:::.    ' *''*    * '.\\'/.' _\\(/_'.':'.'" << endl;
			cout << " : /\\ : :::::     *_\\/_*     -= o =-  /)\\    '  *" << endl;
			cout << "  '..'  ':::'     * /\\ *     .'/.\\'.   '         " << endl;
			cout << "      *            *..*         :                " << endl;
			cout << "       *                                         " << endl;
			cout << "        *                                        " << endl;
		}
	}

}