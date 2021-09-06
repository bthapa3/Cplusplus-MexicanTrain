#pragma once
#include "Player.h"
#include "Tile.h"
#include "Deck.h"
class Round
{	
	public:
		Round() {
			currentRound = 0;
			engineTile = Tile();
			usertrainmarked = false;
			computertrainmarked = false;

		};
		Round(int round) {
			currentRound = round;
			usertrainmarked = false;
			computertrainmarked = false;
		}
		~Round() {};
		void Initializegame();
		void PlayGame();
		void MakeUserMoves();
		void MakeComputerMoves();
	private:
		int currentRound;
		vector <Tile> playerTiles;
		vector <Tile> computerTiles;
		vector <Tile> boneyardTiles;
		vector<Tile> playerTrain;
		vector<Tile> computerTrain;
		vector<Tile> MexicanTrain;
		Tile engineTile;
		bool usertrainmarked;
		bool computertrainmarked;

};

