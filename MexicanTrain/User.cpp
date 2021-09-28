/*
************************************************************
* Name:  Bishal Thapa									   *
* Project:  Project 1 Mexican Train C++				       *
* Class:  CMPS366 OPL				                       *
* Date:  09/27/2020				                           *
************************************************************
*/
#include "User.h"


bool User::PlayMove(Train* trainslist[], vector<Tile> &boneyard, int continuedmove, bool & quit)
{
	cout << "------------Next player: Human----------------" << endl;
	
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
			if (input == 'H') {
				Playsuggestor(trainslist, boneyard, continuedmove);
			}
			if (input == 'S') {
				cout << "serializing" << endl;
				quit = true;
				return false;
			}

			if (input != 'U' && input != 'C' && input != 'M' && input != 'B' && input != 'H') {
				cout << "Invalid option! Please reenter" << endl;
			}
			
		} while (input != 'U' && input != 'C' && input != 'M' && input != 'B' && input != 'H');

		if (input == 'B') {
			
			Tile boneyardtile = boneyard.at(0);
			cout << "_____________________________________________________________________________________" << endl;
			cout << "Picked boneyard tile is: " << boneyardtile.GetSide1() << '-' << boneyardtile.GetSide2() << endl;
			cout << "_____________________________________________________________________________________" << endl;


			//if statement is true only if there was a tile on a boneyard.
			//else turn is skipped 

			if (PickBoneyard(boneyard, **(trainslist))) {
				BoneyardtoTrain(trainslist, replay, validtile,continuedmove);
			}
			else {
				return false;
			}
			
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
					cout << "Press B for Boneyard Tile." << endl;
					cout << ">>";
					cin >> train;
			
				}
				//one more time user can play
				if (train == 'B') {
					//take him to boneyard tile path.
					Tile boneyardtile = boneyard.at(0);
					cout << "Picked boneyard tile is" << boneyardtile.GetSide1() << '-' << boneyardtile.GetSide2() << endl;
					if (PickBoneyard(boneyard, **(trainslist))) {
						BoneyardtoTrain(trainslist, replay, validtile,continuedmove);
					}
					//returns false as the turn doesnot need to be repeated in this case.
					return false;
				}

			}
			
			
			//more validation to be done here.
			if (train == 'U')
			{
				
				if (continuedmove == 1) {

					if (CheckandPlacesecDouble(trainslist, **(trainslist), replay, validtile, "User")) {
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

						CheckandPlacesecDouble(trainslist, **(trainslist + 1), replay, validtile, "Computer");
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

					CheckandPlacesecDouble(trainslist, **(trainslist + 2), replay, validtile, "Mexican");
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



void User::BoneyardtoTrain(Train* trainslist[], bool & replay, bool& validtile , int continuedmove)
{
	Tile toptile = GetPlayerTiles().back();
	char a_train = 'X';
	Tile tile_to_match;
	string dummyinput;
	if (OrphanDoublePresent(trainslist, a_train) && continuedmove==0) {
		validtile = true;
		if (a_train == 'U') {
			if (CheckTrainMove(**(trainslist), toptile, GetPlayerTiles().size())) {
				cout << "Tile added to orphan double train(User train)" << endl;
				cout << "Press Y to continue>>" << endl;
				cin >> dummyinput;
				return;
			}
		}
		else if (a_train == 'C') {
			if (CheckTrainMove(**(trainslist + 1), toptile, GetPlayerTiles().size())) {
				cout << "Tile added to orphan double train(Computer Train)" << endl;
				cout << "Press y to continue>>" << endl;
				cin >> dummyinput;
				return;
			}
		}
		else {
			if (CheckTrainMove(**(trainslist + 2), toptile, GetPlayerTiles().size())) {
				cout << "Tile added to orphan double train(Mexican Train)" << endl;
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
			if (!BoneyardTilePlayable(GetPlayerTiles().back(), trainslist)) {
				validtile = true;
				cout << "Boneyard tile was not playble to any train. Will be placed on the players tile list" << endl;
				string dummyinput;
				cout << "Press y to continue" << endl;
				cin >> dummyinput;
			}
			else {
				char input = DisplayBoneyardOptions();
				if (input == 'U') {
					PlaceCustomTiletoTrain(**(trainslist), replay, validtile, "User", GetPlayerTiles().size());
					(**(trainslist)).RemoveMark();
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
					cout << "Your boneyard tile is playable! Place on the valid train" << endl;
				}
			}
			
		}
	}


}

void User::Playsuggestor(Train* trainslist[], vector<Tile>& boneyard, int continuedmove)
{

	int tilenumber;
	Train train;
	bool turn_repeat = false;
	char traintype;

	//check if there is a orphan double train present
	if (continuedmove == 0 && OrphanDoublePresent(trainslist, traintype)) {
		//move to the orphan double train as needed.
		if (traintype == 'U' && (SuggestOrphanMove(trainslist, **trainslist))) return ;
		if (traintype == 'M' && (SuggestOrphanMove(trainslist, **(trainslist + 2)))) return ;
		if (traintype == 'C' && (SuggestOrphanMove(trainslist, **(trainslist + 1)))) return;

		cout << "You donot have valid tile to play trains. Pick boneyard tiles and mark the train"<< endl;
		cout << "If there are no boneyard tiles left just mark the train and continue" << endl;
		//here needs to be press any key to conitnue.
		return;

	}
	//checks if the mexican train is empty if so adds tile if available.
	if (StartMexicanTrain(trainslist, tilenumber, train)) {
		DisplaySuggestion(tilenumber, train, "it starts the mexican train");
		return ;
	}

	// second argument **trainslist+1 is the train of the opponent player as current player is computer.
	if (Playopponenttrain(trainslist, **(trainslist+1), tilenumber, train)) {
		DisplaySuggestion(tilenumber, train, "the opponent train has marker");
		return ;
	}


	//check if you can force other player to play orphan double train & orphan double cannot be played more than two times.
	if (PlayOrphanDoublemove(trainslist, tilenumber, train, **(trainslist+1)) && continuedmove < 2) {
		Tile mytile = GetPlayerTiles().at(tilenumber - 1);
		if ((continuedmove == 0) || (continuedmove == 1 && ValidsecondDouble(trainslist, train, mytile))) {
			DisplaySuggestion(tilenumber, train, "it forces opponent to play orphan double train");
			return ;
		}
	}


	int mexicantile, mexicansum, selftile, selfsum;
	Train mexicantrain, selftrain;

	bool can_playmexican = PlayMexicanTrain(trainslist, tilenumber, train);
	if (can_playmexican) {
		mexicantile = tilenumber;
		mexicansum = GetPlayerTiles().at(tilenumber - 1).GetSide1() + GetPlayerTiles().at(tilenumber - 1).GetSide2();
		mexicantrain = train;
	}

	bool can_playself = PlaySelfTrain(trainslist, tilenumber, **(trainslist));
	if (can_playself) {
		selftile = tilenumber;
		selfsum = GetPlayerTiles().at(tilenumber - 1).GetSide1() + GetPlayerTiles().at(tilenumber - 1).GetSide2();
		selftrain = **(trainslist);
	}

	//if orphandouble is possible try no to play self train as long  as possible
	//in case of orphan train on opponent this is skipped.
	if (continuedmove == 1) {
		OrphanDoublePresent(trainslist, traintype);
		if (traintype == 'U' && can_playmexican) {
			DisplaySuggestion(mexicantile, **(trainslist + 2), "it is the largest possible tile to play and helps for orphan double");
			return;
		}
		else if (traintype == 'M' && can_playself) {
			DisplaySuggestion(selftile, **(trainslist), "it is the largest possible tile to play and helps for orphan double");
			return;
		}
	}


	if (((can_playmexican && can_playself) && selfsum >= mexicansum) || (can_playself && !can_playmexican)) {

		DisplaySuggestion(selftile, **(trainslist), "it is the largest possible tile to play");
		return;

	}
	else if (((can_playmexican && can_playself) && selfsum < mexicansum) || (!can_playself && can_playmexican)) {

		DisplaySuggestion(mexicantile, **(trainslist + 2), "it is the largest possible tile to play");
		return;
	}
	else {

		cout << "You donot have any valid tiles to play. So pick a tile from boneyard to continue" << endl;
		//DisplayandContinue();
		return;

	}
}


bool User::SuggestOrphanMove(Train* trainslist[], Train& train)
{
	if (CanPlayinTrain(train)) {

		int tilenumber = GetPlayableTile(train);
		DisplaySuggestion(tilenumber, train, "it is the orphan double train");
		return true;
	}
}


void User::DisplaySuggestion(int tilenumber, Train train, string message) {

	string tile = to_string(GetPlayerTiles().at(tilenumber - 1).GetSide1()) + '-' + to_string(GetPlayerTiles().at(tilenumber - 1).GetSide2());
	string trainname = train.trainType();
	cout << "Move tile: " << tile << " to "<< train.trainType() << " as " << message << endl;
	cout << "---------------------------------------------------------------------------------" << endl;
	cout << "Enter y to continue>>";
	string dummyinput;
	cin >> dummyinput;
}

char User::DisplayBoneyardOptions()
{
	char input;
	cout << "Options:" << endl;
	cout << " (U) --> add tile to the User train" << endl;
	cout << " (C) --> add tile to the Computer train" << endl;
	cout << " (M) --> add tile to the Mexican train" << endl;
	cout << " (H) --> get help for the next move" << endl;
	cout << ">>";
	cin >> input;
	return input;
}

bool User::BoneyardTilePlayable(Tile a_tile, Train* trainslist[])
{
	Tile usertrainback = (**trainslist).GetAllTiles().back();
	
	if (usertrainback.GetSide2() == a_tile.GetSide1() || usertrainback.GetSide2() == a_tile.GetSide2()) {
		return true;
	}

	Tile computertrainback = (**(trainslist+1)).GetAllTiles().back();

	if ((**(trainslist + 1)).isTrainMarked()) {
		if (computertrainback.GetSide2() == a_tile.GetSide1() || computertrainback.GetSide2() == a_tile.GetSide2()) {
			return true;
		}

	}
	
	Tile mexicantrainback = (**(trainslist + 2)).GetAllTiles().back();
	if (mexicantrainback.GetSide2() == a_tile.GetSide1() || mexicantrainback.GetSide2() == a_tile.GetSide2()) {
		return true;
	}

	return false;
}


//this function helps to check if 2 douuble tiles are placeable and returns true if the placement is possible.
bool User::CheckandPlacesecDouble(Train* trainslist[], Train& chosenTrain, bool& replay, bool& validtile, string a_player)
{
	int tile_number = GetValidTile();
	bool placement_possible = false;
	Tile userinput = GetTile(tile_number - 1);

	//if player doesnot choose double tile for the second time
	if (userinput.GetSide1() != userinput.GetSide2()) {
		PlaceCustomTiletoTrain(chosenTrain, replay, validtile, a_player, tile_number);
		placement_possible = true;
	}
	//if it is a double tile for second turn
	else {
		//if a train matches a double tile.
		if (chosenTrain.GetTop().GetSide2() == userinput.GetSide1() || chosenTrain.GetTop().GetSide2() == userinput.GetSide1()) {

			//CheckifvalidTileispresent
			bool double_tile_is_valid = ValidsecondDouble(trainslist, chosenTrain, userinput);
			if (double_tile_is_valid) {
				PlaceCustomTiletoTrain(chosenTrain, replay, validtile, a_player, tile_number);
				replay = true;
				placement_possible = true;
			}
			else {
				cout << "Sorry double move cannot be made as you cannot play a single tile after this move" << endl;
			}
		}
		else {
			cout << "invalid tiles to play" << endl;
		}
	}
	return placement_possible;
}



void User::PlaceCustomTiletoTrain(Train& traintype, bool& replay, bool& validtile, string train, int tile_number)
{
	//using the last tile of the player list which is the boneyard tile.
	//int tilenumber = GetPlayerTiles().size();
	int tilenumber = tile_number;
	Tile nextmove = GetPlayerTiles().at(tilenumber - 1);
	//Check TrainMove check if the move to the Train is valid or not and returns true if the 
	//move was successful.
	if (CheckTrainMove(traintype, nextmove, tilenumber)) {
		//this gives one extra chance in condition of OrphanDouble
		if (nextmove.GetSide1() == nextmove.GetSide2()) {
			replay = true;
		}
		validtile = true;
		//only work if the train type is User or computer 
		//traintype.RemoveMark();
	}
	else
	{
		cout << "The tile you chose cannot be placed on the " + train + " train " << endl;

	}
}


void User::PlaceTiletoTrain(Train& traintype, bool& replay, bool& validtile, string train)
{
	//getting the players tile number input from the user.
	int tilenumber = GetValidTile();
	//allows the user to go to back to menu
	if (tilenumber == 0) {
		return;
	}
	Tile nextmove = GetPlayerTiles().at(tilenumber - 1);



	//Check TrainMove checks if the move to the Train is valid or not and returns true if the 
	//move was successful.
	if (CheckTrainMove(traintype, nextmove, tilenumber)) {
		//this gives one extra chance in condition of OrphanDouble
		if (nextmove.GetSide1() == nextmove.GetSide2()) {
			replay = true;
		}
		validtile = true;
	}
	else
	{
		cout << "The tile you chose cannot be placed on the " + train + " train " << endl;

	}

}



char User::Displayoptions()
{
	char input;
	cout << "Options:" << endl;
	cout << " (U) --> add tile to the User train" << endl;
	cout << " (C) --> add tile to the Computer train" << endl;
	cout << " (M) --> add tile to the Mexican train" << endl;
	cout << " (B) --> pick a tile from boneyard/ pass the turn to other player" << endl;
	cout << " (H) --> get help for the next move" << endl;
	cout << " (S) --> serialize and quit" << endl;
	cout << ">>";
	cin >> input;
	return input;

}


int User::GetValidTile()
{
	int tilenumber = 0;
	do
	{
		cout << "Enter a tile number that you want to play!(0 to go back)";
		cout << ">>";
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
		if (tilenumber > GetPlayerTiles().size() || tilenumber < 0) {
			cout << "Tile number out of range!" << endl;
		}
	} while (tilenumber > GetPlayerTiles().size() || tilenumber < 0);
	return tilenumber;
}