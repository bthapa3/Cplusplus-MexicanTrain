#pragma once
#include "Round.h"
class Game
{
	public:
		Game() 
		{
			userfirst = true;
			userscore = 0;
			computerscore = 0;
			currentround = 1;
		}
		void startGame();

	private:

		bool userfirst;
		int userscore;
		int computerscore;
		int currentround;
};

