/*
************************************************************
* Name:  Bishal Thapa									   *
* Project:  Project 1 Mexican Train C++				       *
* Class:  CMPS366 OPL				                       *
* Date:  09/27/2020				                           *
************************************************************
*/

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

	// this plays move for the computer player
	virtual bool PlayMove(Train * trainslist[], vector<Tile>& boneyard, int continuedmove, bool & quit);
	

	//decides if the tile chosen from boneyard can be placed on one of the trains or not based on the user input and train status.
	virtual void BoneyardtoTrain(Train* trainslist[], bool& replay);

	bool checkOrphanandMove(Train * trainslist[], Train & train);


	void DisplayandContinue();

	//This displays information regarding the tile movement to different trains
	void DisplayTileMove(int tilenumber, Train train, string goal);

	//this function helps to repeat a turn of the player in the case he plays a double tile.
	void SetRepeating(bool& replay, int tilenumber);

	//This function helps to move the given tile to the given train.
	void MoveTiletoTrain(Train * trainslist[], int tile, Train  train);
	
};