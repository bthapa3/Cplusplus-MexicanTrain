#include "User.h"

bool User::PlayMove( Train & userTrain, Train& computerTrain, Train& mexicanTrain, vector<Tile> &boneyard)
{
	cout << "This move is made by the user-player" << endl;
	
	unsigned int tilenumber = 0;
	//if the tile chosen can be attached with train chosen.
	bool validtile = false;
	//validating the tilenumber so that user chooses a valid tilenumber to play
	while(!validtile)
	{
		
		do
		{
			cout << "please enter the tile(1-16) you want to pick" << endl;
			cin >> tilenumber;
			

			//Help taken from https://stackoverflow.com/questions/5864540/infinite-loop-with-cin-when-typing-string-while-a-number-is-expected
			//this helps to prevent infinite for loop when string is entered
			if (cin.fail())
			{
				cout << "ERROR -- You did not enter an Input NUmber";

				// get rid of failure state
				cin.clear();
 
				cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

			}

		} while (tilenumber>16 || tilenumber<1);

		
		if (tilenumber >= 1 && tilenumber <= GetPlayerTiles().size())
		{
			char train = 'X';
			//validating the user chosen train
			//User chosen tile to be attached at the end of the train
			Tile nextmove = GetPlayerTiles().at(tilenumber - 1);

			


			while (!(train == 'U' || train == 'C' || train == 'M'))
			{
				cout << "please enter the Train(U-user,C-computer,M-mexican) you want to pick" << endl;
				cin >> train;
				
				char orphandoubletrain = 'X';
				if (OrphanDoublePresent(userTrain, computerTrain, mexicanTrain, orphandoubletrain)) 
				{
					while (train != orphandoubletrain) 
					{
						cout << "You must play on Orphan double Train. Select accordingly!" << endl;
						cin >> train;
					}
					//one more time user can play
					int replay = 1;
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

						}
						else {
							validtile = true;
						}
						
					}
					else
					{
						cout << "The tile you chose cannot be placed on the user train" << endl;

					}
				}
				else if (train == 'C')
				{
					if(computerTrain.isTrainMarked())
					{
						
						//moving  a chosen tile to a computer's train. Only possible when there is 
						//marker at the end of the train.
						if (CheckTrainMove(computerTrain, nextmove, tilenumber)) {
							//this gives one extra chance in condition of OrphanDouble
							if (nextmove.GetSide1() == nextmove.GetSide2()) {
								cout << "You get one more chance to play" << endl;
							}
							else {
								validtile = true;
							}
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
					if (CheckTrainMove(mexicanTrain,nextmove,tilenumber ))
					{
						//this gives one extra chance in condition of OrphanDouble
						if (nextmove.GetSide1() == nextmove.GetSide2()) {
							cout << "You get one more chance to play" << endl;	
						}
						else {
							validtile = true;
						}
					}
					else
					{
						cout << "The tile you chose cannot be placed on the Mexican train" << endl;

					}
				}


			}
		}
		else
		{
			cout << "Tile out of range! Enter a valid tile." << endl;
		}


	}
	return validtile;
}
