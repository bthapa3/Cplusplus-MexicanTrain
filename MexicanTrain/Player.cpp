/*
************************************************************
* Name:  Bishal Thapa									   *
* Project:  Project 1 Mexican Train C++				       *
* Class:  CMPS366 OPL				                       *
* Date:  09/27/2020				                           *
************************************************************
*/


#include "Player.h"

/* *********************************************************************
Function Name:	PlayMove

Purpose:		This is a virutal function so it doesnot do anything.	

Parameters:
				a_trainslist[] --> pointer to the pointers array of train object
				a_boneyard --> vector of boneyard tiles passed by reference.
				a_continuedmove --> integer value which denotes how many times same player has played continously.
				a_quit --> boolean value that represents if the user wants to save the game and quit.

Return Value:
				boolean value that represents if the user gets to make a move again.

Algorithm:
				none

Assistance Received: none
********************************************************************* */

bool Player::PlayMove(Train* a_trainslist[], vector<Tile>& a_boneyard, int a_continuedmove, bool& a_quit)
{
	//This move is made for both players
	//this function doesnot do anything and is a virtual function.
	return false;
}


/* *********************************************************************
Function Name:	CheckTrainMove

Purpose:		Tries to move a given tile to a given train and returns boolean if succesful.

Parameters:
				1) a_Train --> Train where the tile is to be moved passed with reference.
				2) a_tile --> Tile to be moved to the train
				3) a_tilenumber --> integer value that denotes the position of tile in the tile list.

Return Value:
				boolean value that represents if the tile was moves succesfully.

Algorithm:
				check if the one of the tile side has same number as a train. If so move the tile
				and return true value.

Assistance Received: none
********************************************************************* */
bool Player::CheckTrainMove(Train & a_Train, Tile a_tile, int a_tilenumber )
{
	//moving a user chosen tile to a Player train
	if (a_tile.GetSide1() == a_Train.GetAllTiles().back().GetSide2() || a_tile.GetSide2() == a_Train.GetAllTiles().back().GetSide2())
	{

		//if this is a double tile next tile is flipped accordingly
		if (a_Train.GetAllTiles().back().GetSide1() == a_Train.GetAllTiles().back().GetSide2()  && 
			(a_tile.GetSide1() != a_Train.GetAllTiles().back().GetSide2())) 
		{
			a_tile.Filpside();
		}
		//two consecutive tiles are flipped in order to set matching number to each other.
		else if ((a_Train.GetAllTiles().back().GetSide1() != a_Train.GetAllTiles().back().GetSide2()) && 
			a_tile.GetSide1() == a_Train.GetAllTiles().back().GetSide1() || a_tile.GetSide2() == a_Train.GetAllTiles().back().GetSide2()) 
		{
			a_tile.Filpside();
		}
		//adds tile to the Train
		a_Train.Addtile(a_tile);
		//removes tile from the user or computer's tile pile.
		RemoveTile(a_tilenumber - 1);
		return true;
	}
	else
	{
		return false;
	}	
}


/* *********************************************************************
Function Name:	RemoveTile

Purpose:		Remove a player tile at given position.

Parameters:
				1) a_position --> position of the tile in the player's tile list.

Return Value:
				none

Algorithm:
				check for tile and remove if found.

Assistance Received: none
********************************************************************* */
void Player::RemoveTile(int a_position)
{
	//this makes sure random position doesnot break the code.
	if (a_position > m_tileslist.size()) {
		return;
	}
	m_tileslist.erase(m_tileslist.begin() + a_position);
}


/* *********************************************************************
Function Name:	OrphanDoublePresent

Purpose:		Check if the orphan double train is present 

Parameters:
				1) a_trainslist --> pointer to the pointers array of train object
				2) a_train --> character value which stores the type of train if the orphan double train is found.

Return Value:
				boolean value that represents if there was an orphan double train.

Algorithm:
				check if a double tile is present at the end of the train.
				


Assistance Received: none
********************************************************************* */
bool Player::OrphanDoublePresent(Train * a_trainslist[], char & a_train)
{
	
	if ( (**(a_trainslist)).GetAllTiles().size()>1 && (**(a_trainslist)).GetTop().GetSide1() == (**(a_trainslist)).GetTop().GetSide2()) {
		a_train= 'U';
		return true;
	}
	else if ((**(a_trainslist+1)).GetAllTiles().size()>1 && (**(a_trainslist+1)).GetTop().GetSide1() == (**(a_trainslist+1)).GetTop().GetSide2()) {
		a_train= 'C';
		return true;
	}
	else if ((**(a_trainslist+2)).GetAllTiles().size()>1 && (**(a_trainslist+2)).GetTop().GetSide1() == (**(a_trainslist+2)).GetTop().GetSide2()) {
		a_train= 'M';
		return true;
	}
	return false;
}

/* *********************************************************************
Function Name:	PickBoneyard

Purpose:		Pick a tile from boneyard and move to player tiles list if present.

Parameters:
				1) a_boneyard --> vector of boneyard tiles list passed by reference.
				2) a_train --> train where the boneyard tile is to be passed.

Return Value:
				boolean value representing if a boneyard tile was passed succesfully.

Algorithm:
				if size of boneyard tiles is more than 0, pass boneyard tile to player's tiles 
				list. Else mark the train and do nothing.


Assistance Received: none
********************************************************************* */
bool Player::PickBoneyard(vector<Tile> & a_boneyard, Train & a_train)
{
	
	//if there is more tiles left
	if (a_boneyard.size() != 0) {
		Tile boneyardfront = a_boneyard.front();
		a_boneyard.erase(a_boneyard.begin());
		AddtoBack(boneyardfront);
		a_train.MarkTrain();
		return true;
	}
	// if no tiles left simply mark  the train and pass the turn
	else {
		a_train.MarkTrain();
		return false;
	}
	
}


/* *********************************************************************
Function Name:	ValidsecondDouble

Purpose:		Only allow a player to play a second double tile if player has
				a valid single tile to play after second double.

Parameters:
				1)	a_trainslist -->pointer to the pointers array of train object
				2) a_chosentrain --> train where the player is trying to play second double train.
				3) a_newtile -->double tile which the player is trying to play

Return Value:
				boolean value that represents if the user should be allowes to play a second double tile.

Algorithm:
				Modify the top of the train tile as a double tile user choose to play. If remaining player's tiles
				have a tile that can play with one of the trains, tile is a valid second double.


Assistance Received: none
********************************************************************* */

bool Player::ValidsecondDouble(Train* a_trainslist[], Train a_chosentrain, Tile a_newtile)
{
	Tile usertrainTop, computertrainTop, mexicantrainTop;
	if (a_chosentrain.trainType() == "usertrain") {

		usertrainTop = a_newtile;
		computertrainTop = (**(a_trainslist + 1)).GetTop();
		mexicantrainTop = (**(a_trainslist + 2)).GetTop();
	}
	else if (a_chosentrain.trainType() == "computertrain") {

		usertrainTop = (**a_trainslist).GetTop();
		computertrainTop = a_newtile;
		mexicantrainTop = (**(a_trainslist + 2)).GetTop();
	}
	else {
		usertrainTop = (**a_trainslist).GetTop();
		computertrainTop = (**(a_trainslist + 1)).GetTop();
		mexicantrainTop = a_newtile;
	}

	//checking players have a valid single tile to play after second double.
	for (auto& it : GetPlayerTiles()) {
		if ((it.GetSide1() == usertrainTop.GetSide2() || it.GetSide2() == usertrainTop.GetSide2()) && it.GetSide1() != it.GetSide2()) {
			return true;
		}
	}
	if ((**(a_trainslist + 1)).isTrainMarked()) {
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

/* *********************************************************************
Function Name:	BoneyardtoTrain

Purpose:		Virtual function that does nothing

Parameters:
				1)	a_trainslist -->pointer to the pointers array of train object
				2) a_replay --> boolean value that denotes if the user can play a move again continously
				3) a_validtile --> boolean value that represents if the player made a move needed for the turn

Return Value:
				none

Algorithm:
				none

Assistance Received: none
********************************************************************* */
void Player::BoneyardtoTrain(Train* a_trainslist[], bool& a_replay, bool& a_validtile)
{	
	//this is a virtual function that has no work for player class.
			
}

/* *********************************************************************
Function Name:	CanPlayinTrain

Purpose:		Checks if a player has any tile that can be played on the specified train.

Parameters:
				1)	a_train --> train where the tile is to be placed.

Return Value:
				boolean value based on if there is a tile to play

Algorithm:
				check all tiles to match the end of the given train.

Assistance Received: none
********************************************************************* */
bool Player::CanPlayinTrain(Train a_train) {

	//tile where a new tile is attached to the train.
	Tile toptile = a_train.GetTop();

	for (int i = 0; i < GetPlayerTiles().size(); i++) {
		if (GetPlayerTiles().at(i).GetSide1() == toptile.GetSide2() || GetPlayerTiles().at(i).GetSide2() == toptile.GetSide2()) {
			return true;
		}
	}

	return false;
}



/* *********************************************************************
Function Name:	CanPlayDouble

Purpose:		Checks if a player has any double tile that can be played on the specified train.

Parameters:
				1)	a_train --> train where the double tile is to be placed.

Return Value:
				boolean value based on if there is a double tile to play

Algorithm:
				check all double tiles to match the end of the given train.

Assistance Received: none
********************************************************************* */
bool Player::CanPlayDouble(Train a_train)
{
	//tile where a new tile is attached to the train.
	Tile toptile = a_train.GetTop();
	for (int i = 0; i < GetPlayerTiles().size(); i++) {
		if ((GetPlayerTiles().at(i).GetSide1() == toptile.GetSide2() || GetPlayerTiles().at(i).GetSide2() == toptile.GetSide2())
		&& (GetPlayerTiles().at(i).GetSide1()== GetPlayerTiles().at(i).GetSide2())) {
			
			return true;
		}
	}
	return false;
}

/* *********************************************************************
Function Name:	CanPlayNonDouble

Purpose:		Checks if a player has any nondouble tile that can be played on the specified train.

Parameters:
				1)	a_train --> train where the nondouble tile is to be placed.

Return Value:
				boolean value based on if there is a nondouble tile to play

Algorithm:
				check all nondouble tiles to match the end of the given train.

Assistance Received: none
********************************************************************* */
bool Player::CanPlayNonDouble(Train a_train)
{
	//tile where a new tile is attached to the train.
	Tile toptile = a_train.GetTop();
	for (int i = 0; i < GetPlayerTiles().size(); i++) {
		if ((GetPlayerTiles().at(i).GetSide1() == toptile.GetSide2() || GetPlayerTiles().at(i).GetSide2() == toptile.GetSide2())
			&& (GetPlayerTiles().at(i).GetSide1() != GetPlayerTiles().at(i).GetSide2())) {

			return true;
		}
	}
	return false;
}

/* *********************************************************************
Function Name:	GetPlayableTile

Purpose:		return the tile number of the tile that can be played on the given train.

Parameters:
				1)	a_train --> train where the tile is to be placed.

Return Value:
				int value which is the tile number that can be played.

Algorithm:
				check all tiles to match the end of the given train and return tilenumber.

Assistance Received: none
********************************************************************* */
int Player::GetPlayableTile(Train a_train)
{
	//tile where a new tile is attached to the train.
	Tile toptile = a_train.GetTop();
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

/* *********************************************************************
Function Name:	GetPlayableDouble

Purpose:		return the tile number of the doubletile that can be played on the given train.

Parameters:
				1)	a_train --> train where the double tile is to be placed.
Return Value:
				int value which is the double-tile number that can be played.
Algorithm:
				check all double tiles to match the end of the given train and return tilenumber.

Assistance Received: none
********************************************************************* */
int Player::GetPlayableDouble(Train a_train)
{
	//tile where a new tile is attached to the train.
	Tile toptile = a_train.GetTop();
	for (int i = 0; i < GetPlayerTiles().size(); i++) {
		if ((GetPlayerTiles().at(i).GetSide1() == toptile.GetSide2() || GetPlayerTiles().at(i).GetSide2() == toptile.GetSide2())
		&& (GetPlayerTiles().at(i).GetSide1() == GetPlayerTiles().at(i).GetSide2())) {
			return i+1;
		}
	}
	return -1;
}


/* *********************************************************************
Function Name:	StartMexicanTrain

Purpose:		check to place a tile on the mexican train if it has not been started.

Parameters:
				1) a_trainslist[] --> pointer to the pointers array of train object
				2) a_tilenumber --> integer number of the tile which can be played to start the mexican train and
					passed by reference.

Return Value:
				boolean value --> true if mexican train can be started false otherwise. 
Algorithm:
				check if the mexican tile has been started. If not try to start a mexican train.

Assistance Received: none
********************************************************************* */
bool Player::StartMexicanTrain(Train* a_trainslist[], int  & a_tilenumber, Train & a_train)
{
	if ((**(a_trainslist + 2)).Size() == 1 && CanPlayinTrain(**(a_trainslist + 2))) {
	
		a_tilenumber = GetPlayableTile(**(a_trainslist + 2));
		a_train = **(a_trainslist+2) ;
		return true;
			
	}
	else {
		return false;
	}
	
}



/* *********************************************************************
Function Name:	Playopponenttrain

Purpose:		Check if the opponent train can be played and return the tile that can be played

Parameters:
				1)	a_trainslist[] --> pointer to the pointers array of train object
				2) a_opponentTrain --> train where the tile is to be placed
				3) a_tilenumber --> integer number of the tile which can be played to start the mexican train and
					passed by reference.
				4) a_train --> self train of the player.

Return Value:
				boolean value --> true if opponent train can be played.
Algorithm:
				check if opponent train is marked. If yes try to find a tile that can be played
				and return value accordingly.

Assistance Received: none
********************************************************************* */
bool Player::Playopponenttrain( Train * a_trainslist[], Train a_opponentTrain, int & a_tilenumber, Train &  a_train )
{

	//opponent train is just a copy and not reference as it is used for searching a double tile and not modyfying it.
	if (a_opponentTrain.isTrainMarked()) {
		if (CanPlayDouble(a_opponentTrain)) {
			a_tilenumber = GetPlayableDouble(a_opponentTrain);
			a_train = a_opponentTrain;
			return true;

		}
		else if (CanPlayinTrain(a_opponentTrain)) {
			a_tilenumber = GetPlayableTile(a_opponentTrain);
			a_train = a_opponentTrain;
			return true;
		}
	}
	return false;
}



/* *********************************************************************
Function Name:	Playopponenttrain

Purpose:		Check if the Orphandouble move can be played and return the tile that can be played

Parameters:
				1)	a_trainslist --> pointer to the pointers array of train object
				2) a_opponentTrain --> train where the tile is to be placed
				3) a_tilenumber --> integer number of the tile which can be played to start the mexican train and
					passed by reference.
				4) a_train --> self train of the player.

Return Value:
				boolean value --> true if Orphan double move can be played.
Algorithm:
				check if player can play double on a valid train and non double on any other train except the first one.

Assistance Received: none
********************************************************************* */
bool Player::PlayOrphanDoublemove(Train* a_trainslist[], int & a_tilenumber, Train& a_train, Train & a_opponentTrain)
{
	//helps to decide if the opponent train is playable or not.
	bool opponentplayable = a_opponentTrain.isTrainMarked();
	string opponenttrain = a_opponentTrain.trainType();
	if (opponentplayable) {
		//should be able to play double on the user train and non double on any other train.
		if (CanPlayDouble(**a_trainslist)) {
			if (CanPlayNonDouble(**(a_trainslist + 1)) || CanPlayNonDouble(**(a_trainslist + 2))) {
				a_tilenumber= GetPlayableDouble(**a_trainslist);
				a_train=**a_trainslist;
				return true;
			}
		}
		else if (CanPlayDouble(**(a_trainslist+1))) {
			if (CanPlayNonDouble(**(a_trainslist)) || CanPlayNonDouble(**(a_trainslist + 2))) {
				a_tilenumber = GetPlayableDouble(**(a_trainslist+1));
				a_train = **(a_trainslist+1);
				return true;
			}
		}
		else if (CanPlayDouble(**(a_trainslist+2))) {
			if (CanPlayNonDouble(**(a_trainslist)) || CanPlayNonDouble(**(a_trainslist + 1))) {
				a_tilenumber = GetPlayableDouble(**(a_trainslist + 2));
				a_train = **(a_trainslist + 2);
				return true;
			}
		}
		else {
			return false;
		}
	}
	else {
		if (a_opponentTrain.trainType() == "computertrain") {

			if (CanPlayDouble(**a_trainslist)  && CanPlayNonDouble(**(a_trainslist+2)) ) {
				a_tilenumber = GetPlayableDouble(**a_trainslist);
				a_train = **a_trainslist;
				return true;
			}
			else if (CanPlayDouble(**(a_trainslist+2))  && CanPlayNonDouble(**a_trainslist)) {
				a_tilenumber = GetPlayableDouble(**(a_trainslist+2));
				a_train = **(a_trainslist+2);
				return true;
			}

		}
		else if (a_opponentTrain.trainType()=="usertrain") {
			if (CanPlayDouble(**(a_trainslist+1)) && CanPlayNonDouble(**(a_trainslist + 2))) {
				a_tilenumber = GetPlayableDouble(**(a_trainslist+1));
				a_train = **(a_trainslist+1);
				return true;
			}
			else if (CanPlayDouble(**(a_trainslist + 2)) && CanPlayNonDouble(**(a_trainslist+1))) {
				a_tilenumber = GetPlayableDouble(**(a_trainslist + 2));
				a_train = **(a_trainslist + 2);
				return true;
			}
		}
		else {
			return false;
		}
	}
	return false;

}

/* *********************************************************************
Function Name:	PlayMexicanTrain

Purpose:		Check if the move can be played on mexican train and return the tile that can be played

Parameters:
				1) a_trainslist[] --> pointer to the pointers array of train object
				2) a_tilenumber --> integer number of the tile which can be played to start the mexican train and
					passed by reference.
				3) a_train --> mexican train

Return Value:
				boolean value --> true if move can be played on mexican train.
Algorithm:
				check if player can play a tile on a mexican train.
				store the tilenumber on the variable passed by reference.

Assistance Received: none
********************************************************************* */
bool Player::PlayMexicanTrain(Train* a_trainslist[], int& a_tilenumber, Train& a_train)
{
	if (CanPlayinTrain(**(a_trainslist + 2))) {
		a_tilenumber= GetPlayableTile(**(a_trainslist + 2));
		a_train = **(a_trainslist + 2);
		return true;
	}
	return false;
}


/* *********************************************************************
Function Name:	PlaySelfTrain

Purpose:		Check if the move can be played on self train and return the tile that can be played

Parameters:
				1) a_trainslist[] --> pointer to the pointers array of train object
				2) a_tilenumber --> integer number of the tile which can be played to start the mexican train and
					passed by reference.
				3) a_selftrain--> train of the player.

Return Value:
				boolean value --> true if move can be played on self train.
Algorithm:
				check if player can play a tile on a self train.
				store the tilenumber on the variable passed by reference.

Assistance Received: none
********************************************************************* */
bool Player::PlaySelfTrain(Train* a_trainslist[], int& a_tilenumber, Train a_selftrain)
{
	if (CanPlayinTrain(a_selftrain)) {
		a_tilenumber = GetPlayableTile(a_selftrain);
		return true;
	}
	return false;
}



/* *********************************************************************
Function Name:	Getsum

Purpose:		returns the sum of the two sides of a tile.

Parameters:
				1) a_tilenumber --> integer value which helps to find the tile in the tileslist.

Return Value:
				integer value which is sum of two sides.
Algorithm:
				none.

Assistance Received: none
********************************************************************* */
int Player::Getsum(int a_tilenumber)
{
	if (a_tilenumber > GetPlayerTiles().size()) {
		return 0;
	}
	Tile tile = GetPlayerTiles().at(a_tilenumber);
	return tile.GetSide1() + tile.GetSide2();
}
