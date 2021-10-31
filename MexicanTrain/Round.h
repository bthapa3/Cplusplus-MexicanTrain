/*
************************************************************
* Name:  Bishal Thapa									   *
* Project:  Project 1 Mexican Train C++				       *
* Class:  CMPS366 OPL				                       *
* Date:  09/27/2020				                           *
************************************************************
*/

#pragma once
#include "Player.h"
#include "Tile.h"
#include "Deck.h"
#include "User.h"
#include "Computer.h"
#include "Train.h"
#include <iomanip>
#include <fstream>
class Round
{	
	public:
		Round() {
			m_currentRound = 0;
			m_engineTile = Tile();
			m_gameover = false;
			m_playerscore = 0;
			m_computerscore = 0;

		};
		Round(int a_round) {
			m_currentRound = a_round;
			m_gameover = false;
			m_playerscore = 0;
			m_computerscore = 0;
		}
		~Round() {	};
		void Initializegame();
		void DisplayGame();
		bool PlayMoves(bool userfirst, int round, int userscore, int computerscore);
		bool Playpossible();
		inline int playerRoundscore() {
			return m_playerscore;
		}
		inline int computerRoundscore() {
			return m_computerscore;
		}
		void DisplayComputerdouble(int a_spacing);

		void DisplayComputerMiddleTile(int a_spacing);
		void DisplayPlayerMiddleTile(int a_spacing);
		void DisplayPlayerDouble(int a_spacing);

		void DisplayMexicanMiddleTile(int a_spacing);
		void DisplayMexicanDouble(int a_spacing);

		void DisplayallTiles(vector<Tile> a_tiles);

		void SerializeandQuit(int a_userscore, int a_computerscore,string a_nextplayer);

		void InitializefromFile(vector<Tile> a_userTrain, vector<Tile> a_computerTrain, vector<Tile> a_mexicanTrain, bool a_usertrainmarked,
		bool a_computertrainmarked, vector<Tile> a_boneyard, vector<Tile> a_userTiles, vector <Tile> a_computerTiles);


	private:
		int m_currentRound;
		vector <Tile> m_boneyardTiles;
		
		//this is the engine tile
		Tile m_engineTile;

		//this is the boneyard tile
		vector<Tile> m_BoneyardTiles;

		//three trains for the user. mexican and the computer
		Train * m_trainsList[3];
		
		//User player and the computer player
		Player * m_playersList[2];

		
		bool m_gameover;
		int m_playerscore;
		int m_computerscore;
		int m_totalcomputer;
		int m_totalplayer;

};

