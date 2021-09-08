#include "Train.h"

void Train::Addtile(Tile tiletobeadded)
{
	traintiles.push_back(tiletobeadded);
}	

void Train::RemoveTile(int position)
{
	traintiles.erase(traintiles.begin() + position);
}

