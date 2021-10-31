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
			m_side1 = -1;
			m_side2 = -1;
		
		};
		Tile(int firstside, int secondside) {
			m_side1 = firstside;
			m_side2 = secondside;
		}
		~Tile() {};

		inline int GetSide1() {
			return m_side1;
		}
		inline int GetSide2() {
			return m_side2;
		}
		void Filpside();
	private:

		int m_side1;
		int m_side2;
};

