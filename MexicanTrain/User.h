#pragma once
#include "Player.h"
class User : public Player
{
	public:
		User() {};
		User(vector<Tile> tiles):Player(tiles)
		{
		}

};

