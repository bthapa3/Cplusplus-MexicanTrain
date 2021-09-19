#pragma once
#include "Player.h"
#include "Tile.h"
#include "Deck.h"
#include "User.h"
#include "Computer.h"
#include "Train.h"
#include <iomanip>
class Round
{	
	public:
		Round() {
			currentRound = 0;
			engineTile = Tile();
			usertrainmarked = false;
			computertrainmarked = false;
			gameover = false;
			playerscore = 0;
			computerscore = 0;

		};
		Round(int round) {
			currentRound = round;
			usertrainmarked = false;
			computertrainmarked = false;
			gameover = false;
			playerscore = 0;
			computerscore = 0;
		}
		~Round() {};
		void Initializegame();
		void DisplayGame();
		void PlayMoves(bool userfirst);
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

	private:
		int currentRound;
		vector <Tile> boneyardTiles;
		
		Tile engineTile;

		vector<Tile> BoneyardTiles;
		Train * trainsList[3];
		//Train* computerTrain;
		//Train* mexicanTrain;
		//Train* playerTrain;
		Player * playersList[2];
		bool usertrainmarked;
		bool computertrainmarked;
		bool gameover;
		int playerscore;
		int computerscore;

};

