/*
************************************************************
* Name:  Bishal Thapa									   *
* Project:  Project 1 Mexican Train C++				       *
* Class:  CMPS366 OPL				                       *
* Date:  09/27/2020				                           *
************************************************************
*/

#pragma once
#include "Player.h"
#include "Tile.h"
#include "Deck.h"
#include "User.h"
#include "Computer.h"
#include "Train.h"
#include <iomanip>
#include <fstream>
class Round
{	
	public:
		Round() {
			currentRound = 0;
			engineTile = Tile();
			gameover = false;
			playerscore = 0;
			computerscore = 0;

		};
		Round(int round) {
			currentRound = round;
			gameover = false;
			playerscore = 0;
			computerscore = 0;
		}
		~Round() {};
		void Initializegame();
		void DisplayGame();
		bool PlayMoves(bool userfirst, int round, int userscore, int computerscore);
		bool Playpossible();
		inline int playerRoundscore() {
			return playerscore;
		}
		inline int computerRoundscore() {
			return computerscore;
		}
		void DisplayComputerdouble(int spacing);

		void DisplayComputerMiddleTile(int spacing);
		void DisplayPlayerMiddleTile(int spacing);
		void DisplayPlayerDouble(int spacing);

		void DisplayMexicanMiddleTile(int spacing);
		void DisplayMexicanDouble(int spacing);

		void DisplayallTiles(vector<Tile> tiles);

		void SerializeandQuit(int userscore, int computerscore,string nextplayer);

		void InitializefromFile(vector<Tile> userTrain, vector<Tile> computerTrain, vector<Tile> mexicanTrain, bool usertrainmarked,
		bool computertrainmarked, vector<Tile> boneyard, vector<Tile> userTiles, vector <Tile> computerTiles);


	private:
		int currentRound;
		vector <Tile> boneyardTiles;
		
		//this is the engine tile
		Tile engineTile;

		//this is the boneyard tile
		vector<Tile> BoneyardTiles;

		//three trains for the user. mexican and the computer
		Train * trainsList[3];
		
		//User player and the computer player
		Player * playersList[2];

		
		bool gameover;
		int playerscore;
		int computerscore;
		int totalcomputer;
		int totalplayer;

};

