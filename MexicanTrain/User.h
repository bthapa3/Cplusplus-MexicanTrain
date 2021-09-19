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

		virtual bool PlayMove(Train* trainslist[], vector<Tile>& boneyard, int continuedmove);
		
		//decides if the tile chosen from boneyard can be placed on one of the trains or not based on the user input and train status.
		virtual void BoneyardtoTrain(Train* trainslist[], bool& replay, bool& validtile);

};	

