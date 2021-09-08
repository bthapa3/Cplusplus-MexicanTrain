#pragma once

#include <vector>
#include "Tile.h"
#include<string>
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
		
		void PlayMove();
		

	private:
		std::vector <Tile> tileslist;

};

