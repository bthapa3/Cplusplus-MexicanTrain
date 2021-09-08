#pragma once
#include "Player.h"
class Computer : public Player
{
public:
	Computer() {};
	Computer(vector <Tile> tiles) :Player(tiles)
	{
	};
};