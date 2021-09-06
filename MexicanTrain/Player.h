#pragma once

#include <vector>
#include "Tile.h"
#include<string>
using namespace std;
class Player
{
	public:
		Player() {};
		~Player() {};
		inline string addtile(Tile tile) {
			tileslist.push_back(tile);
			return "added";
		}
		inline Tile gettile() {
			
			return tileslist.back();
		}
		bool GetNextTile(Tile& tile);
		

	private:
		std::vector <Tile> tileslist;


};

