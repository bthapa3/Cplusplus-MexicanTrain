/*
************************************************************
* Name:  Bishal Thapa									   *
* Project:  Project 1 Mexican Train C++				       *
* Class:  CMPS366 OPL				                       *
* Date:  09/27/2020				                           *
************************************************************
*/

#pragma once
class Tile
{	
	public:
		
		Tile() {
			side1 = -1;
			side2 = -1;
		
		};
		Tile(int firstside, int secondside) {
			side1 = firstside;
			side2 = secondside;
		}
		~Tile() {};

		inline int GetSide1() {
			return side1;
		}
		inline int GetSide2() {
			return side2;
		}
		void Filpside();
	private:

		int side1;
		int side2;
};

