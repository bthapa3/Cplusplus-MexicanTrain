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

		virtual bool PlayMove(Train* a_trainslist[], vector<Tile>& a_boneyard, int a_continuedmove, bool & a_quit);
		
		//decides if the tile chosen from boneyard can be placed on one of the trains or not based on the user input and train status.
		virtual void BoneyardtoTrain(Train* a_trainslist[], bool& a_replay, bool& a_validtile, int a_continuedmove);

		void Playsuggestor(Train* a_trainslist[], vector<Tile>& a_boneyard, int a_continuedmove);
		
		bool SuggestOrphanMove(Train* a_trainslist[], Train& a_train);
		
		void DisplaySuggestion(int a_tilenumber, Train a_train, string a_message);

		char DisplayBoneyardOptions();
		bool BoneyardTilePlayable(Tile a_tile, Train* a_trainslist[]);

		//checks and places the second double tile if valid.
		bool CheckandPlacesecDouble(Train* a_trainslist[], Train& a_chosenTrain, bool& a_replay, bool& a_validtile, string a_player);

		//place the given tile to the specified train.
		void PlaceCustomTiletoTrain(Train& a_traintype, bool& a_replay, bool& a_validtile, string a_train, int a_tilenumber);

		//allows the users to select a tile to place on the train received as traintype.
		void PlaceTiletoTrain(Train& a_userTrain, bool& a_replay, bool& a_validtile, string a_train);

		//shows options for playing and takes input.
		char Displayoptions();

		//returns a tile number that user picks to play
		int GetValidTile();

};	

