#include "User.h"

bool User::PlayMove( Train & userTrain, Train& computerTrain, Train& mexicanTrain, vector<Tile> &boneyard, int continuedmove)
{
	cout << "-------------USER TURN----------------" << endl;
	
	unsigned int tilenumber = 0;
	//if the tile chosen can be attached with train chosen.
	bool validtile = false;
	bool replay = false;
	//validating the tilenumber so that user chooses a valid tilenumber to play
	while(!validtile)
	{
		
		char input='X';
		
		do {

			//if the same players turn is repeated twice.
			if (continuedmove >= 1) {
				cout << "You got one more move as you played a double tile" << endl;
				cout << "-----------------------------------------------------" << endl;
			}

			
			cout << "Options:" << endl;
			cout << " (U) --> add tile to the User train" << endl;
			cout << " (C) --> add tile to the Computer train" << endl;
			cout << " (M) --> add tile to the Mexican train" << endl;
			cout << " (B) --> pick a tile from boneyard if no valid tile" << endl;
			cout << " (H) --> get help for the next move" << endl;
			cout << " (S) --> serialize and quit" << endl;
			cout << ">>";
			cin >> input;
		} while (input != 'U' && input != 'C' && input != 'M' && input != 'B' && input != 'H' && input != 'S');

		if (input == 'B') {
			PickBoneyard(boneyard,userTrain);
			return false;
		}
		
		else if ((input == 'U' || input == 'C' || input == 'M'))
		{
			
			char train = input;
			char orphandoubletrain = 'X';
			if ((continuedmove < 1) && OrphanDoublePresent(userTrain, computerTrain, mexicanTrain, orphandoubletrain))
			{
				while (train != orphandoubletrain)
				{
					cout << "You must play on Orphan double Train! Select (U) or (C) train!" << endl;
					cout << ">>";
					cin >> train;
				}
				//one more time user can play

			}
			
			
			//more validation to be done here.
			if (train == 'U')
			{
				//getting the players tile number input from the user.
				tilenumber = getValidTile();
				Tile nextmove = GetPlayerTiles().at(tilenumber - 1);
				//Check TrainMove check if the move to the Train is valid or not and returns true if the 
				//move was successful.
				if (CheckTrainMove(userTrain, nextmove, tilenumber)) {
					//this gives one extra chance in condition of OrphanDouble
					if (nextmove.GetSide1() == nextmove.GetSide2()) {
						cout << "You get one more chance to play" << endl;
						replay = true;
					}
					validtile = true;
					userTrain.RemoveMark();
				}
				else
				{
					cout << "The tile you chose cannot be placed on the user train" << endl;

				}
			}
			else if (train == 'C')
			{
				if (computerTrain.isTrainMarked() || orphandoubletrain == 'C')
				{
					//getting the players tile number input from the user.
					//cannot keep these two lines of code outside as input is only asked after checking the validity of train.
					tilenumber = getValidTile();
					Tile nextmove = GetPlayerTiles().at(tilenumber - 1);
					//moving  a chosen tile to a computer's train. Only possible when there is 
					//marker at the end of the train.
					if (CheckTrainMove(computerTrain, nextmove, tilenumber)) {
						//this gives one extra chance in condition of OrphanDouble
						if (nextmove.GetSide1() == nextmove.GetSide2()) {
							cout << "You get one more chance to play" << endl;
							replay = true;
						}
						validtile = true;


					}
					else
					{
						cout << "The tile you chose cannot be placed on the computer's train" << endl;

					}

				}
				else {
					cout << "You cannot add tiles to unmarked computer's train" << endl;
				}

			}
			else if (train == 'M')
			{
				//getting the players tile number input from the user.
				tilenumber = getValidTile();
				Tile nextmove = GetPlayerTiles().at(tilenumber - 1);
				//moving a user chosen tile to a Computer train
				if (CheckTrainMove(mexicanTrain, nextmove, tilenumber))
				{
					//this gives one extra chance in condition of OrphanDouble
					if (nextmove.GetSide1() == nextmove.GetSide2()) {
						cout << "You get one more chance to play" << endl;
						replay = true;

					}
					validtile = true;

				}
				else
				{
					cout << "The tile you chose cannot be placed on the Mexican train" << endl;

				}
			}
			else {
				cout << "Sorry the tile you gave cannot be played on the chosen Train! Pick Boneyard tiles if no moves are valid." << endl;
			}


		}

	}
	return replay;
}


