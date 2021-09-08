#pragma once
#include <vector>
#include <string>
#include "Tile.h"
using namespace std;

class Train
{
	public:
		Train() { trainmarked = false; };
		Train( string typeoftrain ) 
		{
			typeoftrain = typeoftrain;
			trainmarked = false;
		}
		void Addtile(Tile tiletobeadded);

		void RemoveTile(int position);

		//returns all the tiles of the train
		inline vector<Tile> GetAllTiles() {
			return traintiles;
		};
		inline bool isTrainMarked() {
			return trainmarked;
		}

	private:
		vector<Tile> traintiles;
		string typeoftrain;
		bool trainmarked;
};

