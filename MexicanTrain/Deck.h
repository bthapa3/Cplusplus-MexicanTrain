/*
************************************************************
* Name:  Bishal Thapa									   *
* Project:  Project 1 Mexican Train C++				       *
* Class:  CMPS366 OPL				                       *
* Date:  09/27/2020				                           *
************************************************************
*/

#pragma once
#include "Tile.h"
#include <vector>
#include <iostream>
#include <ctime>
#include <algorithm>

using namespace std;
class Deck
{
	public:
		Deck() {
			for (int i = 0;i <= 9;i++) {
				for (int j = i; j <= 9;j++) 
				{
					Tile newTile = Tile(i, j);
					m_deck.push_back(newTile);
				}
			}
		}
		inline vector<Tile> GetDeck() {
			return m_deck;
		}
		//for shuffling the deck
		void ShuffleDeck();
		//helper function that helps for shuffling the tiles properly.
		int GenerateRandomNumber(int range);
		//returns the EngineTile for starting the Game
		Tile GetEngineTile(int round);
		//returns the players tiles
		vector<Tile> GetPlayerTiles();
		//returns the Computers Tiles
		vector<Tile> GetComputerTiles();
		//returns the Boneyard Tiles
		vector<Tile> GetBoneyardTiles();

	private:
		vector <Tile> m_deck;
};

