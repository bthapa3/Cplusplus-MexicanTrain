#pragma once
#include "Player.h"
#include <iostream>

class Computer : public Player
{
public:
	Computer() {};
	Computer(vector <Tile> tiles) :Player(tiles)
	{
	};

	// this plays move for the computer player
	virtual bool PlayMove(Train * trainslist[], vector<Tile>& boneyard, int continuedmove);
	

	//decides if the tile chosen from boneyard can be placed on one of the trains or not based on the user input and train status.
	virtual void BoneyardtoTrain(Train* trainslist[], bool& replay, bool& validtile);
	
};