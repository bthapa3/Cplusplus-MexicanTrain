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
			m_userfirst = false;
			m_userscore = 0;
			m_computerscore = 0;
			m_currentround = 1;
			m_initializedfromfile = false;
		
		}
		void StartGame();

		inline void addComputerscore(int a_score) {
			m_computerscore = m_computerscore + a_score;
		}
		inline void addUserscore(int a_score) {
			m_userscore = m_userscore + a_score;
		}
		inline int getUserscore() {
			return m_userscore;
		}
		inline int getComputerscore() {
			return m_computerscore;
		}
		inline void setInitializedfromFile(bool a_isinitialized) {
			m_initializedfromfile = a_isinitialized;

		}

		inline bool isInitializedfromFile() {
			return m_initializedfromfile;
		}
		inline void setUserfirst(bool a_userfirst) {
			m_userfirst = a_userfirst;
		}
		inline bool isUserfirst() {
			return m_userfirst;
		}

		bool ReadfromFile(bool& computertrainmarked, bool& usertrainmarked, Round & newround);

		void LineSplitter(string str, vector<string>& vect);

		string TrimSpace(string& s);

	private:

		bool m_userfirst;
		int m_userscore;
		int m_computerscore;
		int m_currentround;
		bool m_initializedfromfile;
};

