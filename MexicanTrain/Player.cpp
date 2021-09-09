#include "Player.h"



void Player::addtile(Tile tile)
{
	tileslist.push_back(tile);
}

bool Player::CheckTrainMove(Train& Train, Tile tile, int tilenumber)
{
	//moving a user chosen tile to a Player train
	if (tile.GetSide1() == Train.GetAllTiles().back().GetSide2() || tile.GetSide2() == Train.GetAllTiles().back().GetSide2())
	{
		
		//if this is a double tile next tile is flipped accordingly
		if (Train.GetAllTiles().back().GetSide1() == Train.GetAllTiles().back().GetSide2()  && tile.GetSide1() != Train.GetAllTiles().back().GetSide2()) {
			tile.Filpside();
		}
		//two consecutive tiles are flipped in order to set matching number to each other.
		else if (tile.GetSide1() == Train.GetAllTiles().back().GetSide1()) {
			tile.Filpside();
		}
		//adds tile to the Train
		Train.Addtile(tile);
		//removes tile from the user or computer's tile pile.
		RemoveTile(tilenumber - 1);
		return true;
	}
	else
	{
		return false;

	}	
}

void Player::RemoveTile(int position)
{
	tileslist.erase(tileslist.begin() + position);
}



bool Player::OrphanDoublePresent(Train& userTrain, Train& computerTrain, Train& mexicanTrain, char & train)
{
	
	if ( userTrain.GetAllTiles().size()>1 && userTrain.GetTop().GetSide1() == userTrain.GetTop().GetSide2()) {
		train= 'U';
		return true;
	}
	else if ( computerTrain.GetAllTiles().size()>1 && computerTrain.GetTop().GetSide1() == computerTrain.GetTop().GetSide2()) {
		train= 'C';
		return true;
	}
	else if ( mexicanTrain.GetAllTiles().size()>1 && mexicanTrain.GetTop().GetSide1() == mexicanTrain.GetTop().GetSide2()) {
		train= 'M';
		return true;
	}
	return false;
}



void Player::Mainmove(Train& userTrain, Train& computerTrain, Train& mexicanTrain, vector<Tile>& boneyard) {
	
	cout << "This is the main move" << endl;
	
	
	PlayMove(userTrain, computerTrain, mexicanTrain, boneyard);
	
}

void Player::WinningMove(Train& userTrain, Train& computerTrain, Train& mexicanTrain, vector<Tile>& boneyard)
{
	//get all the end of the tiles of the train to get the winning strategy


}

bool Player::PlayMove(Train& userTrain, Train& computerTrain, Train& mexicanTrain, vector<Tile>& boneyard)
{
	cout << "This move is made for both players" << endl;
	return false;
}



