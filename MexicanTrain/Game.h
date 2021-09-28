/*
************************************************************
* Name:  Bishal Thapa									   *
* Project:  Project 1 Mexican Train C++				       *
* Class:  CMPS366 OPL				                       *
* Date:  09/27/2020				                           *
************************************************************
*/

#pragma once
#include "Round.h"
class Game
{
	public:
		Game() 
		{
			userfirst = false;
			userscore = 0;
			computerscore = 0;
			currentround = 1;
			initializedfromfile = false;
		
		}
		void StartGame();

		inline void addComputerscore(int score) {
			computerscore = computerscore + score;
		}
		inline void addUserscore(int score) {
			userscore = userscore + score;
		}
		inline int getUserscore() {
			return userscore;
		}
		inline int getComputerscore() {
			return computerscore;
		}
		inline void setInitializedfromFile(bool a_isinitialized) {
			initializedfromfile = a_isinitialized;

		}

		inline bool isInitializedfromFile() {
			return initializedfromfile;
		}
		inline void setUserfirst(bool a_userfirst) {
			userfirst = a_userfirst;
		}
		inline bool isUserfirst() {
			return userfirst;
		}

		void LineSplitter(string str, vector<string>& vect);

		string TrimSpace(string& s);

	private:

		bool userfirst;
		int userscore;
		int computerscore;
		int currentround;
		bool initializedfromfile;
};

