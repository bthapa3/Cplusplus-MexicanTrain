/*
************************************************************
* Name:  Bishal Thapa									   *
* Project:  Project 1 Mexican Train C++				       *
* Class:  CMPS366 OPL				                       *
* Date:  09/27/2020				                           *
************************************************************
*/
#include "Train.h"

/* *********************************************************************
Function Name:	    Addtile

Purpose:          Adds a given tile to the end of the tiles list.

Parameters:
			  a_tiletobeadded --> Tile object which needs to be added to the end of the train.


Return Value:
			   none.
Algorithm:
			   none.

Assistance Received: none
********************************************************************* */
void Train::Addtile(Tile a_tiletobeadded)
{
	m_traintiles.push_back(a_tiletobeadded);
}	

