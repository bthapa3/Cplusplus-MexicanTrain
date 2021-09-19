#include "Computer.h"

bool Computer::PlayMove(Train* trainslist[], vector<Tile>& boneyard,int continuedmove)
{
	
	
	
	
	WinningStrategy(trainslist,boneyard);

	
	
	return false;
	
	
	
	
	
	
	
	/*cout << "-------------COMPUTER TURN----------------" << endl;


	unsigned int tilenumber = 0;
	//if the tile chosen can be attached with train chosen.
	bool validtile = false;
	bool replay = false;
	//validating the tilenumber so that user chooses a valid tilenumber to play
	while (!validtile)
	{
		char input = 'X';
		
		do {

			//if the same players turn is repeated twice.
			if (continuedmove >= 1) {
				cout << "You got one more move as you played a double tile" << endl;
				cout << "-----------------------------------------------------" << endl;
			}

			//printing all the eligible options to the user

			input = Displayoptions();
		} while (input != 'U' && input != 'C' && input != 'M' && input != 'B' && input != 'H' && input != 'S');

		if (input == 'B') {
			
			
			Tile boneyardtile = boneyard.at(0);
			cout << "_____________________________________________________________________________________" << endl;
			cout << "Picked boneyard tile is: " << boneyardtile.GetSide1() << '-' << boneyardtile.GetSide2() << endl;
			cout << "Place it to a valid train or press B again to skip your turn" << endl;
			cout << "_____________________________________________________________________________________" << endl;


			//if statement is true only if there was a tile on a boneyard.
			//else turn is skipped 
			if (PickBoneyard(boneyard, **(trainslist + 1))) {
				BoneyardtoTrain(trainslist, replay, validtile);
			}
			return false;
		}
		
		else if ((input == 'U' || input == 'C' || input == 'M'))
		{
			
			char train = input;
			char orphandoubletrain = 'X';
			if ((continuedmove < 1) && OrphanDoublePresent(trainslist , orphandoubletrain))
			{
				while (train != orphandoubletrain && train != 'B')
				{
					cout << "You must play on Orphan double Train! or Select boneyard tiles!" << endl;
					cout << ">>";
					cin >> train;
				}
				//one more time user can play
				if (train == 'B') {
					//take him to boneyard tile path.
					Tile boneyardtile = boneyard.at(0);
					cout << "Picked boneyard tile is" << boneyardtile.GetSide1() << '-' << boneyardtile.GetSide2() << endl;
					if (PickBoneyard(boneyard, **(trainslist + 1))) {
						BoneyardtoTrain(trainslist , replay, validtile);
					}
					return false;
				}

			}
			

			//more validation to be done here.
			if (train == 'C')
			{
				if (continuedmove == 1) {

					if (CheckandPlace(trainslist, **(trainslist + 1), replay, validtile, "Computer")) {
						(**(trainslist + 1)).RemoveMark();
					}
				}
				else {
					PlaceTiletoTrain(**(trainslist + 1), replay, validtile, "Computer");
					if ((**(trainslist + 1)).isTrainMarked())
					{
						(**(trainslist + 1)).RemoveMark();
					}
				}
				
				
			}
			else if (train == 'U')
			{
				if ((**(trainslist)).isTrainMarked() || orphandoubletrain == 'U')
				{
					if (continuedmove == 1) {

						CheckandPlace(trainslist, **(trainslist),replay, validtile, "User");
					}
					else {
						PlaceTiletoTrain(**(trainslist), replay, validtile, "User");
					}

				}
				else {
					cout << "You cannot add tiles to unmarked user's train" << endl;
				}

			}
			else if (train == 'M')
			{

				if (continuedmove == 1) {

					CheckandPlace(trainslist, **(trainslist + 2), replay, validtile, "Mexican");
				}
				else {
					PlaceTiletoTrain(**(trainslist + 2), replay, validtile, "Mexican");
				}	
		
			}
			else {
				cout << "Sorry the tile you gave cannot be played on the chosen Train! Pick Boneyard tiles if no moves are valid." << endl;
			}

		}
	}
	return replay;*/
}

void Computer::BoneyardtoTrain(Train* trainslist[], bool& replay, bool& validtile)
{
}


