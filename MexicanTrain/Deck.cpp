/*
************************************************************
* Name:  Bishal Thapa									   *
* Project:  Project 1 Mexican Train C++				       *
* Class:  CMPS366 OPL				                       *
* Date:  09/27/2020				                           *
************************************************************
*/

#include "Deck.h"
#include "Tile.h"


/* *********************************************************************
Function Name:	ShuffleDeck

Purpose:		This function helps to shuffle a deck by using random number generation.
				A new deck is created with random order of tiles and stored at deck.
Parameters:
			none

Return Value:
			none

Algorithm:
			pick random number in the range of deck size and move that tile in m_deck 
			to shuffled deck until m_deck is empty. Assign shuffled deck back to m_deck.


Assistance Received: None
********************************************************************* */

void Deck::ShuffleDeck(){

	
	vector <Tile> shuffleddeck;
	while (m_deck.size() != 0) {

		//getting a random tile from the deck
		int position= GenerateRandomNumber(m_deck.size());
	
		//pushing to the shuffled deck starting at position 0 as vector starts from 0.
		shuffleddeck.push_back(m_deck.at(position-1));

		//erasing the currently chosen tile from the initial deck.
		m_deck.erase(m_deck.begin() + position-1);

	}

	m_deck = shuffleddeck;
}

/* *********************************************************************
Function Name:	GetEngineTile

Purpose:		Return engine tile and remove the tile from the shuffled list which will be later
				assigned to the players.
Parameters:
				a_round --> integer round value which denote what the tile is going to be

Return Value:
				Tile which denotes the engine tile.

Algorithm:
				Find the engine tile from the tiles list based on round number and return the tile back.


Assistance Received: None
********************************************************************* */
Tile Deck::GetEngineTile(int a_round) {
	
	//this helps when the round is greater than 100.
	while (a_round > 10) { 
		a_round = a_round % 10; 
	}
	int tilenumber;

	//sets tilevalue to 0 if round r is divisible by 10.
	if (a_round % 10 == 0) 
	{
		tilenumber = 0;
	}
	//sets the tile values accordingly
	else 
	{
		tilenumber = 10 - a_round % 10;
	} 
	Tile enginetile =  Tile(tilenumber,tilenumber);
	//removes the engine tile from the current deck.
	//deck.erase(std::remove(deck.begin(), deck.end(), enginetile), deck.end());
	int currentposition = 0;
	for (auto& it : m_deck) {
		
		// check the current engine tile and remove it from deck so that user donot get the same value.
		if (it.GetSide1() == tilenumber && it.GetSide2() == tilenumber)
		{
			m_deck.erase(m_deck.begin() + currentposition);
		}
		currentposition++;
	}

	return enginetile;	
};


/* *********************************************************************
Function Name:	GetPlayerTiles

Purpose:		Returns 16 tiles from the tiles list to the human player
Parameters:
				none

Return Value:
				vector of 16 tiles assigned to the human player

Algorithm:
				Give the first 16 tiles of the shuffled list to the human. 
				Delete 16 tiles from the list


Assistance Received: None
********************************************************************* */
vector<Tile> Deck::GetPlayerTiles() {

	vector<Tile> playertiles;
	for (int i= 0; i < 16;i++) {
		playertiles.push_back(m_deck.front());
		m_deck.erase(m_deck.begin());
	}
	return playertiles;

};

/* *********************************************************************
Function Name:	GetComputerTiles

Purpose:		Returns 16 tiles from the tiles list to the computer player
Parameters:
				none

Return Value:
				vector of 16 tiles assigned to the computer player

Algorithm:
				Give the first 16 tiles of the shuffled list to the computer.
				Delete 16 tiles from the list


Assistance Received: None
********************************************************************* */
vector<Tile> Deck::GetComputerTiles() {
	vector<Tile> computertiles;
	for (int i = 0; i < 16;i++) {
		computertiles.push_back(m_deck.front());
		m_deck.erase(m_deck.begin());
	}
	return computertiles;

};

/* *********************************************************************
Function Name:	GetBoneyardTiles()

Purpose:		Returns 22 tiles from the tiles list to the boneyard
Parameters:
				none

Return Value:
				vector of 22 tiles assigned to the boneyard.

Algorithm:
				Give 22 tiles of the shuffled list to the boneyard and delete fron the list.


Assistance Received: None
********************************************************************* */
vector<Tile> Deck::GetBoneyardTiles() 
{
	vector<Tile> bonyardtiles;
	for (int i = 0; i < 22;i++) {
		bonyardtiles.push_back(m_deck.front());
		m_deck.erase(m_deck.begin());
	}
	return bonyardtiles;
};


/* *********************************************************************
Function Name:	GenerateRandomNumber

Purpose:		Generate a random number in the given range.
Parameters:
				1)a_range --> integer which denotes the range of random number to be generated.

Return Value:
				int value in the given range.

Algorithm:
				none

Assistance Received: None
********************************************************************* */
int Deck::GenerateRandomNumber(int a_range) {
	srand((unsigned)time(0));
	int randomNumber;

	randomNumber = (rand() % a_range) + 1;
	return randomNumber;

}