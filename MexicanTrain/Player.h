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

		void Mainmove(Train& userTrain, Train& computerTrain, Train& mexicanTrain, vector<Tile>& boneyard) {
			cout << "This is the main move" << endl;
			PlayMove( userTrain,  computerTrain,  mexicanTrain, boneyard);
		}
		
		virtual void PlayMove(Train& userTrain, Train& computerTrain, Train& mexicanTrain, vector<Tile>& boneyard);
		

	private:
		std::vector <Tile> tileslist;

};

