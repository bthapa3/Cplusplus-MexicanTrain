#include "Player.h"



void Player::addtile(Tile tile)
{
	tileslist.push_back(tile);
}

void Player::RemoveTile(int position)
{
	tileslist.erase(tileslist.begin() + position);
}

void Player::PlayMove(Train& userTrain, Train& computerTrain, Train& mexicanTrain, vector<Tile>& boneyard)
{
	cout << "This move is made for both players" << endl;
}



