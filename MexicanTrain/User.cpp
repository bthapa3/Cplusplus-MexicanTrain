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
			PickBoneyard(boneyard);
			return false;
		}
		
		else if ((input == 'U' || input == 'C' || input == 'M'))
		{
			
			Tile nextmove = GetPlayerTiles().at(getValidTile() - 1);
			char train = input;
			char orphandoubletrain = 'X';
			if ((continuedmove < 1) && OrphanDoublePresent(userTrain, computerTrain, mexicanTrain, orphandoubletrain))
			{
				while (train != orphandoubletrain)
				{
					cout << "You must play on Orphan double Train. Select accordingly!" << endl;
					cin >> train;
				}
				//one more time user can play

			}

			//more validation to be done here.
			if (train == 'U')
			{

				//Check TrainMove check if the move to the Train is valid or not and returns true if the 
				//move was successful.
				if (CheckTrainMove(userTrain, nextmove, tilenumber)) {
					//this gives one extra chance in condition of OrphanDouble
					if (nextmove.GetSide1() == nextmove.GetSide2()) {
						cout << "You get one more chance to play" << endl;
						replay = true;
					}
					validtile = true;

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


