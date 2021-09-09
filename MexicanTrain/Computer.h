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

	virtual bool PlayMove(Train& userTrain, Train& computerTrain, Train& mexicanTrain, vector<Tile>& boneyard, int continuedmove);
};