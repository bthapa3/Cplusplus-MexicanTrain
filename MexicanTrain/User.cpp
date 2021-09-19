#include "User.h"
using namespace std;

bool User::PlayMove(Train* trainslist[], vector<Tile> &boneyard, int continuedmove)
{
	cout << "-------------USER TURN----------------" << endl;
	
	unsigned int tilenumber = 0;
	//if the tile chosen can be attached with train chosen.
	bool validtile = false;
	bool replay = false;
	bool boneyardtile = false;
	//validating the tilenumber so that user chooses a valid tilenumber to play
	while(!validtile)
	{
		
		char input='X';
		
		do {

			//if the same players turn is repeated twice.
			if (continuedmove >= 1) {
				cout << "You have one more move as you played a double tile" << endl;
				cout << "-----------------------------------------------------" << endl;
			}

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

			if (PickBoneyard(boneyard, **(trainslist))) {
				BoneyardtoTrain(trainslist, replay, validtile);
			}
			return false;
			
		}
		
		if ((input == 'U' || input == 'C' || input == 'M'))
		{
			
			char train = input;
			char orphandoubletrain = 'X';

			//if a player has to play a orphan double train or pickup a boneyard tile


			if ((continuedmove < 1) && OrphanDoublePresent(trainslist, orphandoubletrain))
			{   
				while (train != orphandoubletrain && train !='B')
				{
					cout << "You must play on Orphan double Train! or Select boneyard tile" << endl;
					cout << ">>";
					cin >> train;
					

				}
				//one more time user can play
				if (train == 'B') {
					//take him to boneyard tile path.
					Tile boneyardtile = boneyard.at(0);
					cout << "Picked boneyard tile is" << boneyardtile.GetSide1() << '-' << boneyardtile.GetSide2() << endl;
					if (PickBoneyard(boneyard, **(trainslist))) {
						BoneyardtoTrain(trainslist, replay, validtile);
					}
					return false;
				}

			}
			
			
			//more validation to be done here.
			if (train == 'U')
			{
				
				if (continuedmove == 1) {

					if (CheckandPlace(trainslist, **(trainslist), replay, validtile, "User")) {
						(**(trainslist)).RemoveMark();
					}
				}
				else {
					PlaceTiletoTrain(**(trainslist), replay, validtile, "User");
					if ((**(trainslist)).isTrainMarked())
					{
						(**(trainslist)).RemoveMark();
					}
				}
				
			}
			else if (train == 'C')
			{
				
				if ((**(trainslist+1)).isTrainMarked() || orphandoubletrain == 'C')
				{
					if (continuedmove == 1) {

						CheckandPlace(trainslist, **(trainslist + 1), replay, validtile, "Computer");
					}
					else {
						PlaceTiletoTrain(**(trainslist + 1), replay, validtile, "Computer");
					}	
		
				}
				else {
					cout << "You cannot add tiles to unmarked computer's train" << endl;
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
	return replay;
}



void User::BoneyardtoTrain(Train* trainslist[], bool& replay, bool& validtile)
{
	Tile toptile = GetPlayerTiles().back();
	char a_train = 'X';
	Tile tile_to_match;
	string dummyinput;
	if (OrphanDoublePresent(trainslist, a_train)) {
		if (a_train == 'U') {
			if (CheckTrainMove(**(trainslist), toptile, GetPlayerTiles().size())) {
				cout << "Tile added to orphan double train" << endl;
				cout << "Press Y to continue>>" << endl;
				cin >> dummyinput;
				return;
			}
		}
		else if (a_train == 'C') {
			if (CheckTrainMove(**(trainslist + 1), toptile, GetPlayerTiles().size())) {
				cout << "Tile added to orphan double train" << endl;
				cout << "Press y to continue>>" << endl;
				cin >> dummyinput;
				return;
			}
		}
		else {
			if (CheckTrainMove(**(trainslist + 2), toptile, GetPlayerTiles().size())) {
				cout << "Tile added to orphan double train" << endl;
				cout << "Press y to continue>>" << endl;
				cin >> dummyinput;
				return;
			}
		}

		cout << "------------------------------------------------------------------------------" << endl;
		cout << "Tile doesnot fit for the orphan double train! Will be added to the players list " << endl;
		cout << " Press y to continue" << endl;
		cin >> dummyinput;
		cout << "------------------------------------------------------------------------------" << endl;

	}
	else {
		while (!validtile)
		{
			char input = Displayoptions();
			if (input == 'B') {
				validtile = true;
			}
			else if (input == 'U') {
				PlaceCustomTiletoTrain(**(trainslist), replay, validtile, "User", GetPlayerTiles().size());
				(**(trainslist + 1)).RemoveMark();
			}
			else if (input == 'C')
			{
				if ((**(trainslist + 1)).isTrainMarked())
				{

					PlaceCustomTiletoTrain(**(trainslist + 1), replay, validtile, "Computer", GetPlayerTiles().size());

				}
				else {
					cout << "You cannot add tiles to unmarked computer's train" << endl;
				}

			}
			else if (input == 'M') {
				PlaceCustomTiletoTrain(**(trainslist + 2), replay, validtile, "Mexican", GetPlayerTiles().size());
			}
			else {
				cout << "Sorry Cannot use boneyard tile! Please pass turn by choosing B" << endl;
			}
		}
	}


}






