/*
************************************************************
* Name:  Bishal Thapa									   *
* Project:  Project 1 Mexican Train C++				       *
* Class:  CMPS366 OPL				                       *
* Date:  09/27/2020				                           *
************************************************************
*/
#include "Train.h"

void Train::Addtile(Tile tiletobeadded)
{
	traintiles.push_back(tiletobeadded);
}	

void Train::RemoveTile(int position)
{
	if (position > traintiles.size()) {
		cout << "Invalid position to remove tile from" << endl;
		return;
	}
	traintiles.erase(traintiles.begin() + position);
}

