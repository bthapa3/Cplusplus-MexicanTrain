/*
************************************************************
* Name:  Bishal Thapa									   *
* Project:  Project 1 Mexican Train C++				       *
* Class:  CMPS366 OPL				                       *
* Date:  09/27/2020				                           *
************************************************************
*/


#include "Player.h"
bool Player::PlayMove(Train* trainslist[], vector<Tile>& boneyard, int continuedmove, bool& quit)
{
	//This move is made for both players
	//this function doesnot do anything and is a virtual function.
	return false;
}

bool Player::CheckTrainMove(Train & Train, Tile tile, int tilenumber )
{
	//moving a user chosen tile to a Player train
	if (tile.GetSide1() == Train.GetAllTiles().back().GetSide2() || tile.GetSide2() == Train.GetAllTiles().back().GetSide2())
	{

		//if this is a double tile next tile is flipped accordingly
		if (Train.GetAllTiles().back().GetSide1() == Train.GetAllTiles().back().GetSide2()  && 
			(tile.GetSide1() != Train.GetAllTiles().back().GetSide2())) 
		{
			tile.Filpside();
		}
		//two consecutive tiles are flipped in order to set matching number to each other.
		else if ((Train.GetAllTiles().back().GetSide1() != Train.GetAllTiles().back().GetSide2()) && 
			tile.GetSide1() == Train.GetAllTiles().back().GetSide1() || tile.GetSide2() == Train.GetAllTiles().back().GetSide2()) 
		{
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
	//this makes sure random position doesnot break the code.
	if (position > tileslist.size()) {
		return;
	}
	tileslist.erase(tileslist.begin() + position);
}



bool Player::OrphanDoublePresent(Train * trainslist[], char & train)
{
	
	if ( (**(trainslist)).GetAllTiles().size()>1 && (**(trainslist)).GetTop().GetSide1() == (**(trainslist)).GetTop().GetSide2()) {
		train= 'U';
		return true;
	}
	else if ((**(trainslist+1)).GetAllTiles().size()>1 && (**(trainslist+1)).GetTop().GetSide1() == (**(trainslist+1)).GetTop().GetSide2()) {
		train= 'C';
		return true;
	}
	else if ((**(trainslist+2)).GetAllTiles().size()>1 && (**(trainslist+2)).GetTop().GetSide1() == (**(trainslist+2)).GetTop().GetSide2()) {
		train= 'M';
		return true;
	}
	return false;
}


bool Player::PickBoneyard(vector<Tile> &boneyard, Train & train)
{
	
	//if there is more tiles left
	if (boneyard.size() != 0) {
		Tile boneyardfront = boneyard.front();
		boneyard.erase(boneyard.begin());
		AddtoBack(boneyardfront);
		train.MarkTrain();
		return true;
	}
	// if no tiles left simply mark  the train and pass the turn
	else {
		train.MarkTrain();
		return false;
	}
	
}


bool Player::ValidsecondDouble(Train* trainslist[], Train chosentrain, Tile newtile)
{
	Tile usertrainTop, computertrainTop, mexicantrainTop;
	if (chosentrain.trainType() == "usertrain") {

		usertrainTop = newtile;
		computertrainTop = (**(trainslist + 1)).GetTop();
		mexicantrainTop = (**(trainslist + 2)).GetTop();
	}
	else if (chosentrain.trainType() == "computertrain") {

		usertrainTop = (**trainslist).GetTop();
		computertrainTop = newtile;
		mexicantrainTop = (**(trainslist + 2)).GetTop();
	}
	else {
		usertrainTop = (**trainslist).GetTop();
		computertrainTop = (**(trainslist + 1)).GetTop();
		mexicantrainTop = newtile;
	}

	//checking players have a valid single tile to play after second double.
	for (auto& it : GetPlayerTiles()) {
		if ((it.GetSide1() == usertrainTop.GetSide2() || it.GetSide2() == usertrainTop.GetSide2()) && it.GetSide1() != it.GetSide2()) {
			return true;
		}
	}
	if ((**(trainslist + 1)).isTrainMarked()) {
		for (auto& it : GetPlayerTiles()) {
			if ((it.GetSide1() == computertrainTop.GetSide2() || it.GetSide2() == computertrainTop.GetSide2()) && it.GetSide1() != it.GetSide2()) {
				return true;
			}
		}

	}
	for (auto& it : GetPlayerTiles()) {
		if ((it.GetSide1() == mexicantrainTop.GetSide2() || it.GetSide2() == mexicantrainTop.GetSide2()) && it.GetSide1() != it.GetSide2()) {
			return true;
		}
	}
	return false;


}

void Player::BoneyardtoTrain(Train* trainslist[], bool& replay, bool& validtile)
{	
	//this is a virtual function that has no work for player class.
			
}




bool Player::CanPlayinTrain(Train train) {

	Tile toptile = train.GetTop();

	for (int i = 0; i < GetPlayerTiles().size(); i++) {
		if (GetPlayerTiles().at(i).GetSide1() == toptile.GetSide2() || GetPlayerTiles().at(i).GetSide2() == toptile.GetSide2()) {
			return true;
		}
	}

	return false;
}



bool Player::CanPlayDouble(Train train)
{
	Tile toptile = train.GetTop();
	for (int i = 0; i < GetPlayerTiles().size(); i++) {
		if ((GetPlayerTiles().at(i).GetSide1() == toptile.GetSide2() || GetPlayerTiles().at(i).GetSide2() == toptile.GetSide2())
		&& (GetPlayerTiles().at(i).GetSide1()== GetPlayerTiles().at(i).GetSide2())) {
			
			return true;
		}
	}
	return false;
}

bool Player::CanPlayNonDouble(Train train)
{
	Tile toptile = train.GetTop();
	for (int i = 0; i < GetPlayerTiles().size(); i++) {
		if ((GetPlayerTiles().at(i).GetSide1() == toptile.GetSide2() || GetPlayerTiles().at(i).GetSide2() == toptile.GetSide2())
			&& (GetPlayerTiles().at(i).GetSide1() != GetPlayerTiles().at(i).GetSide2())) {

			return true;
		}
	}
	return false;
}

int Player::GetPlayableTile(Train train)
{
	Tile toptile = train.GetTop();
	int tile_return = -1;
	for (int i = 0; i < GetPlayerTiles().size(); i++) {
		if (GetPlayerTiles().at(i).GetSide1() == toptile.GetSide2() || GetPlayerTiles().at(i).GetSide2() == toptile.GetSide2()) {
			
			if (tile_return > -1) {
				if (Getsum(i) > Getsum(tile_return)) {
					tile_return = i;
				}
			}
			else {
				tile_return = i;
			}
			
			
		}
	}
	return tile_return+1;
}

int Player::GetPlayableDouble(Train train)
{
	Tile toptile = train.GetTop();
	for (int i = 0; i < GetPlayerTiles().size(); i++) {
		if ((GetPlayerTiles().at(i).GetSide1() == toptile.GetSide2() || GetPlayerTiles().at(i).GetSide2() == toptile.GetSide2())
		&& (GetPlayerTiles().at(i).GetSide1() == GetPlayerTiles().at(i).GetSide2())) {
			return i+1;
		}
	}
	return -1;
}





bool Player::StartMexicanTrain(Train* trainslist[], int  & tilenumber, Train & train)
{
	if ((**(trainslist + 2)).Size() == 1 && CanPlayinTrain(**(trainslist + 2))) {
	
		tilenumber = GetPlayableTile(**(trainslist + 2));
		train = **(trainslist+2) ;
		return true;
			
	}
	else {
		return false;
	}
	
}



bool Player::Playopponenttrain( Train * trainslist[], Train opponentTrain, int & tilenumber, Train &  train )
{

	//opponent train is just a copy and not reference as it is used for searching a double tile and not modyfying it.
	if (opponentTrain.isTrainMarked()) {
		if (CanPlayDouble(opponentTrain)) {
			tilenumber = GetPlayableDouble(opponentTrain);
			train = opponentTrain;
			return true;

		}
		else if (CanPlayinTrain(opponentTrain)) {
			tilenumber = GetPlayableTile(opponentTrain);
			train = opponentTrain;
			return true;

		}


	}
	return false;
}


bool Player::PlayOrphanDoublemove(Train* trainslist[], int & tilenumber, Train& train, Train & opponentTrain)
{
	bool opponentplayable = opponentTrain.isTrainMarked();
	string opponenttrain = opponentTrain.trainType();
	if (opponentplayable) {
		//should be able to play double on the user train and non double on any other train.
		if (CanPlayDouble(**trainslist)) {
			if (CanPlayNonDouble(**(trainslist + 1)) || CanPlayNonDouble(**(trainslist + 2))) {
				tilenumber= GetPlayableDouble(**trainslist);
				train=**trainslist;
				return true;
			}
		}
		else if (CanPlayDouble(**(trainslist+1))) {
			if (CanPlayNonDouble(**(trainslist)) || CanPlayNonDouble(**(trainslist + 2))) {
				tilenumber = GetPlayableDouble(**(trainslist+1));
				train = **(trainslist+1);
				return true;
			}
		}
		else if (CanPlayDouble(**(trainslist+2))) {
			if (CanPlayNonDouble(**(trainslist)) || CanPlayNonDouble(**(trainslist + 1))) {
				tilenumber = GetPlayableDouble(**(trainslist + 2));
				train = **(trainslist + 2);
				return true;
			}
		}
		else {
			return false;
		}
	}
	else {
		if (opponentTrain.trainType() == "computertrain") {

			if (CanPlayDouble(**trainslist)  && CanPlayNonDouble(**(trainslist+2)) ) {
				tilenumber = GetPlayableDouble(**trainslist);
				train = **trainslist;
				return true;
			}
			else if (CanPlayDouble(**(trainslist+2))  && CanPlayNonDouble(**trainslist)) {
				tilenumber = GetPlayableDouble(**(trainslist+2));
				train = **(trainslist+2);
				return true;
			}

		}
		else if (opponentTrain.trainType()=="usertrain") {
			if (CanPlayDouble(**(trainslist+1)) && CanPlayNonDouble(**(trainslist + 2))) {
				tilenumber = GetPlayableDouble(**(trainslist+1));
				train = **(trainslist+1);
				return true;
			}
			else if (CanPlayDouble(**(trainslist + 2)) && CanPlayNonDouble(**(trainslist+1))) {
				tilenumber = GetPlayableDouble(**(trainslist + 2));
				train = **(trainslist + 2);
				return true;
			}
		}
		else {
			return false;
		}
	}
	return false;

}

bool Player::PlayMexicanTrain(Train* trainslist[], int& tilenumber, Train& train)
{
	if (CanPlayinTrain(**(trainslist + 2))) {
		tilenumber= GetPlayableTile(**(trainslist + 2));
		train = **(trainslist + 2);
		return true;
	}
	return false;
}

bool Player::PlaySelfTrain(Train* trainslist[], int& tilenumber, Train selftrain)
{
	if (CanPlayinTrain(selftrain)) {
		tilenumber = GetPlayableTile(selftrain);
		return true;
	}
	return false;
}


int Player::Getsum(int tilenumber)
{
	if (tilenumber > GetPlayerTiles().size()) {
		return 0;
	}
	Tile tile = GetPlayerTiles().at(tilenumber);
	return tile.GetSide1() + tile.GetSide2();
}
