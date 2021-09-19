#pragma once

#include <vector>
#include "Tile.h"
#include<string>
#include <iostream>
#include "Train.h"
using namespace std;
class Player
{
	public:

		//constructor methods
		Player() {};
		Player(vector<Tile> playertiles){
			tileslist = playertiles;
		}

		//destructor method
		~Player() {};

		//allows adding tile to the player list.
		void addtile(Tile tile) ;
		
		//this tries to move tile to a specific train and returns true if possible
		//it move was possible tile is already moved to the given train
		bool CheckTrainMove(Train& Train, Tile tile, int tilenumber);


		//returns all the tiles list of the users
		inline vector<Tile> GetPlayerTiles() {
			return tileslist;
		}

		//this helps to return tile at a specific position
		inline Tile gettile(int position) {
			
			return tileslist.at(position);
		}
		//to add the tile as push-back
		inline void AddtoBack(Tile tile) {
			tileslist.push_back(tile);
		}
		//remove the tile at specific position.
		void RemoveTile(int position);

		//checks if orphan double is present or not
		bool OrphanDoublePresent(Train * trainslist[], char & train);

		//this is the main move played by both computer and player users.
		bool Mainmove(Train * trainlist[], vector<Tile>& boneyard, int continuedplay); 

		//this winning strategy is used by computer player for playing and user player for getting hints.
		void WinningStrategy(Train * trainslist[], vector<Tile>& boneyard);
		
		//this virtual function allows player class to have polymorphism. playmove allows computer and player users to play differently.
		virtual bool PlayMove(Train* trainslist[], vector<Tile>& boneyard, int continuedmove);

		//this function helps to pick a front tile from the boneyard and move to the player's tile list.
		bool PickBoneyard(vector<Tile> &boneyard, Train & train);

		//returns a tile number that user picks to play
		int getValidTile();

		//shows options for playing and takes input.
		char Displayoptions();

		//allows the users to select a tile to place on the train received as traintype.
		void PlaceTiletoTrain(Train& userTrain, bool& replay, bool& validtile, string train);

		//place the given tile to the specified train.
		void PlaceCustomTiletoTrain(Train& traintype, bool& replay, bool& validtile, string train, int tilenumber);

		//whenever player plays two continue times this method is used to decide if the player can play third time or not based on the next tile chosen.
		bool validsecondDouble(Train* trainslist[], Train chosentrain, Tile newtile);

		//decides if the tile chosen from boneyard can be placed on one of the trains or not based on the user input and train status.
		virtual void BoneyardtoTrain(Train* trainslist[], bool& replay, bool& validtile);
        
		//checks and places the second double tile if valid.
		bool CheckandPlace(Train* trainslist[], Train& chosenTrain, bool& replay, bool& validtile, string a_player);

		//checks if the user should play a mexican train
		//bool startMexicanTrain(Train* trainslist[], Train& traintoplay, Tile& tiletoplay, int & tilenumber);

		//this function returns if any tile among the list can be used to play in the train.
		bool CanPlayinTrain(Train train);

		//this function returns if a player can play a double tile 
		bool CanPlayDouble(Train train);

		//this function returns a playable single tile or double tile from all tiles 
		int GetPlayableTile(Train train);
		
		//this function returns a playable double tile
		int GetPlayableDouble(Train train);

		//this function returns a guaranteed playable non-double tile
		int GetPlayableNonDouble(Train train);

		//checks if there is a non double tile that can be played
		bool CanPlayNonDouble(Train train);

		//this function will chose the tiles to start a mexican train if the train is not yet started.
		bool StartMexicanTrain(Train* trainslist[], int & tilenumber,Train & train);

		//This function helps to move the given tile to the given train.
		void MoveTiletoTrain(Train * trainslist[], int tile, Train  train);

		//this function checks if opponent train is marked and then tries to play double tile or a valid single tile.
		bool Playopponenttrain(Train* trainslist[], Train opponentTrain, int& tilenumber, Train& train);

		//this function tries to play a orphan double move in order to force opponent to play or pick.
		bool PlayOrphanDoublemove(Train* trainslist[], int& tilenumber, Train& train, Train & opponentTrain);

		bool PlayMexicanTrain(Train* trainslist[], int& tilenumber, Train& train);

		bool PlaySelfTrain(Train* trainslist[], int& tilenumber, Train selftrain);

	private:
		std::vector <Tile> tileslist;


};

