/*
************************************************************
* Name:  Bishal Thapa									   *
* Project:  Project 1 Mexican Train C++				       *
* Class:  CMPS366 OPL				                       *
* Date:  09/27/2020				                           *
************************************************************
*/

#pragma once
#include <vector>
#include <string>
#include "Tile.h"
#include <iostream>
using namespace std;

class Train
{
	public:

		Train() {
		}
		Train( string a_train ) 
		{
			m_typeoftrain = a_train;
			m_trainmarked = false;
		}
		~Train() {};
		void Addtile(Tile a_tiletobeadded);


		//returns all the tiles of the train
		inline vector<Tile> GetAllTiles() {

			return m_traintiles;
		};

		inline bool isTrainMarked() {
			return m_trainmarked;
		};


		inline Tile GetTop() {
			return m_traintiles.back();
		}
		inline void MarkTrain() {
			m_trainmarked = true;
		}
		inline void RemoveMark() {
			m_trainmarked = false;
		}
		inline int Size() {
			return m_traintiles.size();
		}
		inline string trainType() {
			return m_typeoftrain;
		}

	private:
		vector<Tile> m_traintiles;
		string m_typeoftrain;
		bool m_trainmarked;
		
};

