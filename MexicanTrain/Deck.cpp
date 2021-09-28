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


//This function helps to shuffle a deck by using random number generation
//A new deck is created with random order of tiles and restored at deck.

void Deck::ShuffleDeck(){

	//deck.erase(deck.begin() + 1);
	//deck.pop_back();
	//myvector.at(i);
	vector <Tile> shuffleddeck;
	while (deck.size() != 0) {

		//getting a random tile from the deck
		int position= GenerateRandomNumber(deck.size());
	
		//pushing to the shuffled deck starting at position 0 as vector starts from 0.
		shuffleddeck.push_back(deck.at(position-1));

		//erasing the currently chosen tile from the initial deck.
		deck.erase(deck.begin() + position-1);

	}

	deck = shuffleddeck;
}



Tile Deck::GetEngineTile(int round) {
	
	//this helps when the round is greater than 100.
	while (round > 10) { 
		round = round % 10; 
	}
	int tilenumber;

	//sets tilevalue to 0 if round r is divisible by 10.
	if (round % 10 == 0) 
	{
		tilenumber = 0;
	}
	//sets the tile values accordingly
	else 
	{
		tilenumber = 10 - round % 10;
	} 
	Tile enginetile =  Tile(tilenumber,tilenumber);
	//removes the engine tile from the current deck.
	//deck.erase(std::remove(deck.begin(), deck.end(), enginetile), deck.end());
	int currentposition = 0;
	for (auto& it : deck) {
		
		// check the current engine tile and remove it from deck so that user donot get the same value.
		if (it.GetSide1() == tilenumber && it.GetSide2() == tilenumber)
		{
			deck.erase(deck.begin() + currentposition);
		}
		currentposition++;
	}

	return enginetile;	
};


//returns the players tiles
vector<Tile> Deck::GetPlayerTiles() {

	vector<Tile> playertiles;
	for (int i= 0; i < 16;i++) {
		playertiles.push_back(deck.front());
		deck.erase(deck.begin());
	}
	return playertiles;

};
//returns the Computers Tiles

vector<Tile> Deck::GetComputerTiles() {
	vector<Tile> computertiles;
	for (int i = 0; i < 16;i++) {
		computertiles.push_back(deck.front());
		deck.erase(deck.begin());
	}
	return computertiles;

};
//returns the Boneyard Tiles
vector<Tile> Deck::GetBoneyardTiles() 
{
	vector<Tile> bonyardtiles;
	for (int i = 0; i < 22;i++) {
		bonyardtiles.push_back(deck.front());
		deck.erase(deck.begin());
	}
	return bonyardtiles;
};


//this function generates the random number between 1 and the range
int Deck::GenerateRandomNumber(int range) {
	srand((unsigned)time(0));
	int randomNumber;

	randomNumber = (rand() % range) + 1;
	return randomNumber;

}