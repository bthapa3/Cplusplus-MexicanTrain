#include "User.h"

void User::PlayMove( Train & userTrain, Train& computerTrain, Train& mexicanTrain, vector<Tile> &boneyard)
{
	cout << "This move is made by the user-player" << endl;

	
	

	
	/*unsigned int tilenumber = 0;
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
				//more validation to be done here.
				if (train == 'U')
				{

					//moving a user chosen tile to a Player train
					if (nextmove.GetSide1() == userTrain.GetAllTiles().back().GetSide1() || nextmove.GetSide2() == userTrain.GetAllTiles().back().GetSide1())
					{
						userTrain.Addtile(nextmove);
						RemoveTile( tilenumber - 1);
						validtile = true;
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
						//moving a user chosen tile to a Computer train
						if (nextmove.GetSide1() == computerTrain.GetAllTiles().back().GetSide1() || 
							nextmove.GetSide2() == computerTrain.GetAllTiles().back().GetSide1())
						{
							computerTrain.Addtile(nextmove);
							RemoveTile( tilenumber - 1);
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
					if (nextmove.GetSide1() == mexicanTrain.GetAllTiles().back().GetSide1() || 
						nextmove.GetSide2() == mexicanTrain.GetAllTiles().back().GetSide1())
					{
						mexicanTrain.Addtile(nextmove);
						RemoveTile( tilenumber - 1);
						validtile = true;
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
			cout << "Enter a valid tile" << endl;
		}


	}*/
}
