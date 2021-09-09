#pragma once
#include "Player.h"
#include <string>
#include <iostream>
#include "Train.h"
#include "Tile.h"
class User : public Player
{
	public:
		User() {};
		User(vector<Tile> tiles):Player(tiles)
		{
		}
		virtual bool PlayMove(Train& userTrain, Train& computerTrain, Train& mexicanTrain, vector<Tile>& boneyard, int continuedmove);
	    
};

