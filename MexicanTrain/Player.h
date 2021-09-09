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

		//destructor methos
		~Player() {};


		void addtile(Tile tile) ;
		
		//this tries to move tile to a specific train and returns true if possible
		//online checks the matching tile given tile marker is already checked.
		bool CheckTrainMove(Train& Train, Tile tile, int tilenumber);
		//returns all the tiles list of the users
		inline vector<Tile> GetPlayerTiles() {
			return tileslist;
		}

		//this helps to return tile at a specific position
		inline Tile gettile(int position) {
			
			return tileslist.at(position);
		}
		inline void AddtoBack(Tile tile) {
			tileslist.push_back(tile);
		}
		void RemoveTile(int position);

		//checks if orphan double is present or not
		bool OrphanDoublePresent(Train& userTrain, Train& computerTrain, Train& mexicanTrain, char & train);

		void Mainmove(Train& userTrain, Train& computerTrain, Train& mexicanTrain, vector<Tile>& boneyard); 

		void WinningMove(Train& userTrain, Train& computerTrain, Train& mexicanTrain, vector<Tile>& boneyard);
		
		virtual bool PlayMove(Train& userTrain, Train& computerTrain, Train& mexicanTrain, vector<Tile>& boneyard);

		
		

	private:
		std::vector <Tile> tileslist;

};

