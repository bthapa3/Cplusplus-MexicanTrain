/*
************************************************************
* Name:  Bishal Thapa									   *
* Project:  Project 1 Mexican Train C++				       *
* Class:  CMPS366 OPL				                       *
* Date:  09/27/2020				                           *
************************************************************
*/

#include "Tile.h"

void Tile::Filpside()
{
	int temp = side1;
	side1 = side2;
	side2 = temp;
}
