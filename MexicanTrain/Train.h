#pragma once
#include <vector>
#include <string>
#include "Tile.h"
using namespace std;

class Train
{
	public:

		Train() {
		}
		Train( string train ) 
		{
			typeoftrain = train;
			trainmarked = false;
			orphandoubled = false;
		}
		~Train() {};
		void Addtile(Tile tiletobeadded);

		void RemoveTile(int position);

		//returns all the tiles of the train
		inline vector<Tile> GetAllTiles() {

			return traintiles;
		};

		inline bool isTrainMarked() {
			return trainmarked;
		};

		inline string marked() {
			if (trainmarked) return "ON";
			else return "OFF";
		}

		inline Tile GetTop() {
			return traintiles.back();
		}
		inline void MarkTrain() {
			trainmarked = true;
		}
		inline void RemoveMark() {
			trainmarked = false;
		}
		inline int Size() {
			return traintiles.size();
		}
		inline string trainType() {
			return typeoftrain;
		}

	private:
		vector<Tile> traintiles;
		string typeoftrain;
		bool trainmarked;
		bool orphandoubled;
};

