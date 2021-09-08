#pragma once
#include <vector>
#include <string>
#include "Tile.h"
using namespace std;

class Train
{
	public:
		Train() {};
		Train( string typeoftrain ) 
		{
			typeoftrain = typeoftrain;
		}
		void Addtiles(Tile tiletobeadded);
		//returns all the tiles of the train
		inline vector<Tile> ReturnAllTiles() {
			return traintiles;
		};

	private:
		vector<Tile> traintiles;
		string typeoftrain;
};

