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
#include <string>
#include <iostream>
#include "Train.h"
#include "Tile.h"
using namespace std;
class User : public Player
{
	public:
		User() {};
		User(vector<Tile> tiles):Player(tiles)
		{
		}

		virtual bool PlayMove(Train* trainslist[], vector<Tile>& boneyard, int continuedmove, bool & quit);
		
		//decides if the tile chosen from boneyard can be placed on one of the trains or not based on the user input and train status.
		virtual void BoneyardtoTrain(Train* trainslist[], bool& replay, bool& validtile, int continuedmove);

		void Playsuggestor(Train* trainslist[], vector<Tile>& boneyard, int continuedmove);
		
		bool SuggestOrphanMove(Train* trainslist[], Train& train);
		
		void DisplaySuggestion(int tilenumber, Train train, string message);

		char DisplayBoneyardOptions();
		bool BoneyardTilePlayable(Tile a_tile, Train* trainslist[]);

		//checks and places the second double tile if valid.
		bool CheckandPlacesecDouble(Train* trainslist[], Train& chosenTrain, bool& replay, bool& validtile, string a_player);

		//place the given tile to the specified train.
		void PlaceCustomTiletoTrain(Train& traintype, bool& replay, bool& validtile, string train, int tilenumber);

		//allows the users to select a tile to place on the train received as traintype.
		void PlaceTiletoTrain(Train& userTrain, bool& replay, bool& validtile, string train);

		//shows options for playing and takes input.
		char Displayoptions();

		//returns a tile number that user picks to play
		int GetValidTile();

};	

