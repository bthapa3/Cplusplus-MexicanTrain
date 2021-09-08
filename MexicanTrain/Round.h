#pragma once
#include "Player.h"
#include "Tile.h"
#include "Deck.h"
#include "User.h"
#include "Computer.h"
#include "Train.h"
class Round
{	
	public:
		Round() {
			currentRound = 0;
			engineTile = Tile();
			usertrainmarked = false;
			computertrainmarked = false;
			gameover = false;


		};
		Round(int round) {
			currentRound = round;
			usertrainmarked = false;
			computertrainmarked = false;
			gameover = false;
		}
		~Round() {};
		void Initializegame();
		void DisplayGame();
		void PlayMoves();
		void MakeComputerMoves();
	private:
		int currentRound;
		vector <Tile> boneyardTiles;
		
		Tile engineTile;

		vector<Tile> BoneyardTiles;
		Train* computerTrain;
		Train* mexicanTrain;
		Train* playerTrain;
		Player * playersList[2];
		bool usertrainmarked;
		bool computertrainmarked;
		bool gameover;

};

