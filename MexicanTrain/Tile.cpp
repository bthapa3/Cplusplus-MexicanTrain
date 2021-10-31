/*
************************************************************
* Name:  Bishal Thapa									   *
* Project:  Project 1 Mexican Train C++				       *
* Class:  CMPS366 OPL				                       *
* Date:  09/27/2020				                           *
************************************************************
*/

#include "Tile.h"

/* *********************************************************************
Function Name:	    Flipside

Purpose:          This function helps to change the sides of the tile to display accordingly.

Parameters:
               none


Return Value:
               none.
Algorithm:
              assign side1 to side2 and side2 to side1.

Assistance Received: none
********************************************************************* */
void Tile::Filpside()
{
	int temp = m_side1;
	m_side1 = m_side2;
	m_side2 = temp;
}
