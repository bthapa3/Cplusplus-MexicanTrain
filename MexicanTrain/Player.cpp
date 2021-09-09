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



bool Player::Mainmove(Train& userTrain, Train& computerTrain, Train& mexicanTrain, vector<Tile>& boneyard, int continuedplay) {
	
	cout << "This is the main move" << endl;
	
	
	bool replay= PlayMove(userTrain, computerTrain, mexicanTrain, boneyard, continuedplay);


	return replay;
	
}

void Player::WinningMove(Train& userTrain, Train& computerTrain, Train& mexicanTrain, vector<Tile>& boneyard)
{
	//get all the end of the tiles of the train to get the winning strategy


}

bool Player::PlayMove(Train& userTrain, Train& computerTrain, Train& mexicanTrain, vector<Tile>& boneyard, int continuedmove)
{
	cout << "This move is made for both players" << endl;
	return false;
}


void Player::PickBoneyard(vector<Tile> boneyard)
{
	Tile boneyardfront = boneyard.front();
	boneyard.erase(boneyard.begin());
	AddtoBack(boneyardfront);
}

int Player::getValidTile()
{
	int tilenumber=0;
	do
	{

		cout << "Enter a tile number that you want to play!";
		cout << ">>";
		cin >> tilenumber;


		//Help taken from https://stackoverflow.com/questions/5864540/infinite-loop-with-cin-when-typing-string-while-a-number-is-expected
		//this helps to prevent infinite for loop when string is entered
		if (cin.fail())
		{
			cout << "ERROR -- You did not enter an Input NUmber";

			// get rid of failure state
			cin.clear();

			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		}
		if (tilenumber > GetPlayerTiles().size() || tilenumber < 1) {
			cout << "Tile number out of range!" << endl;
		}
	} while (tilenumber > GetPlayerTiles().size() || tilenumber < 1);
	return tilenumber;
}


