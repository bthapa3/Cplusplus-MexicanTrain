/*
************************************************************
* Name:  Bishal Thapa									   *
* Project:  Project 1 Mexican Train C++				       *
* Class:  CMPS366 OPL				                       *
* Date:  09/27/2020				                           *
************************************************************
*/
#include "User.h"


/* *********************************************************************
Function Name:	PlayMove

Purpose:		This function helps the human player to make next move by taking inputs and checking 
				train and tiles chosen are valid. It also provides help as needed by displaying 
				information.

Parameters:
				a_trainslist[] --> pointer to the pointers array of train object
				a_boneyard --> vector of boneyard tiles passed by reference.
				a_continuedmove --> integer value which denotes how many times same player has played continously.
				a_quit --> boolean value that represents if the user wants to save the game and quit.

Return Value:
			  boolean --> which denotes if the user can make one more move continously.
Algorithm:
			  take input from the user to find train and tiles to play. If not valid ask for input again.


Assistance Received: none
********************************************************************* */
bool User::PlayMove(Train* trainslist[], vector<Tile> &boneyard, int continuedmove, bool & quit)
{
	cout << "------------Next player: Human----------------" << endl;
	
	unsigned int tilenumber = 0;
	//if the tile chosen can be attached with train chosen.
	bool validtile = false;
	bool replay = false;
	//validating the tilenumber so that user chooses a valid tilenumber to play
	while(!validtile)
	{
		//user input for next move.
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


/* *********************************************************************
Function Name:	BoneyardtoTrain

Purpose:		This function helps the human player to make next move by taking inputs and checking
				train and tiles chosen are valid. It also provides help as needed by displaying
				information.

Parameters:
				1)	a_trainslist[] --> pointer to the pointers array of train object
				2)	replay --> boolean object that determines if the user can make one more continous move.
				3)	validtile --> boolean value that denotes if a player has made a move that completes his turn.	
				4) continuedmove --> integer value which denotes how many times same player has played before continously.	

Return Value:
			  none.
Algorithm:
			  
				Take top tile from the usertilelist i.e the first tile
					If orphan double present 
						-check if the tile can be played on the orphan double train
						-If orphan double tile is not playable display and return
					If orphan double not present
						-Find a matching train to place the tile
						-If not train are valid, display and return.

Assistance Received: none
********************************************************************* */
void User::BoneyardtoTrain(Train* trainslist[], bool & replay, bool& validtile , int continuedmove)
{
	//toptile has a tile that was just moved from boneyard tileslist to playerstile list
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



/* *********************************************************************
Function Name:	Playsuggestor

Purpose:		This function is used to help the human player to decide to make the next move.
				It is similar to computer play move function but it doesnot make a move but just displays the message.

Parameters:
				1)	a_trainslist[] --> pointer to the pointers array of train object
				2) boneyard --> vector of boneyard tiles passed with reference.
				3) continuedmove --> integer value which denotes how many times same player has played before continously.

Return Value:
			  none.
Algorithm:

				If orphan train present and this is not a continous second turn:
					- Check if can play orphan double train and suggest tile
					- If not suggest to pick boneyard tile
				else-
					-if playing for first time try to start mexican train
					-try to play orphan double train
					-try to play opponent train
					-if a double tile played before avoid playing on same train
					-try playing biggest tile on one of user or mexican train
					-pick tile from boneyard

Assistance Received: none
********************************************************************* */
void User::Playsuggestor(Train* trainslist[], vector<Tile>& boneyard, int continuedmove)
{

	int tilenumber;
	Train train;
	bool turn_repeat = false;
	char traintype;

	//Priority goes from up to down.
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

	
	//check if you can force other player to play orphan double train & orphan double cannot be played more than two times.
	if (PlayOrphanDoublemove(trainslist, tilenumber, train, **(trainslist+1)) && continuedmove < 2) {
		Tile mytile = GetPlayerTiles().at(tilenumber - 1);
		if ((continuedmove == 0) || (continuedmove == 1 && ValidsecondDouble(trainslist, train, mytile))) {
			DisplaySuggestion(tilenumber, train, "it forces opponent to play orphan double train");
			return ;
		}
	}

	// second argument **trainslist+1 is the train of the opponent player as current player is computer.
	if (Playopponenttrain(trainslist, **(trainslist + 1), tilenumber, train)) {
		DisplaySuggestion(tilenumber, train, "the opponent train has marker");
		return;
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


/* *********************************************************************
Function Name:	SuggestOrphanMove

Purpose:		This function helps to display a tile, if a tile is playable on the orphan double train.

Parameters:
				1)	a_trainslist[] --> pointer to the pointers array of train object
				2)	a_train --> orphan double train to be played.

Return Value:
				boolean value --> true if orphan double train can be played false otherwise.
Algorithm:

				Check if can play in orphan double train
				-display tile number and train to move.

Assistance Received: none
********************************************************************* */
bool User::SuggestOrphanMove(Train* a_trainslist[], Train& a_train)
{
	if (CanPlayinTrain(a_train)) {

		int tilenumber = GetPlayableTile(a_train);
		DisplaySuggestion(tilenumber, a_train, "it is the orphan double train");
		return true;
	}
}


/* *********************************************************************
Function Name:	DisplaySuggestion

Purpose:		This function is used to display the message on the train and tiles suggested by the helper
				function. It takes tile , train and the message as input parameters.

Parameters:
				1)	a_tilnumber --> tile to be played
				2) a_ train --> train to be played to.
				3) a_message --> reasoning of why to play to specified train.

Return Value:
				none.
Algorithm:

				none.

Assistance Received: none
********************************************************************* */
void User::DisplaySuggestion(int tilenumber, Train train, string message) {

	//tile in string format
	string tile = to_string(GetPlayerTiles().at(tilenumber - 1).GetSide1()) + '-' + to_string(GetPlayerTiles().at(tilenumber - 1).GetSide2());
	//trainname in string format
	string trainname = train.trainType();
	cout << "Move tile: " << tile << " to "<< train.trainType() << " as " << message << endl;
	cout << "---------------------------------------------------------------------------------" << endl;
	cout << "Enter y to continue>>";
	string dummyinput;
	cin >> dummyinput;
}


/* *********************************************************************
Function Name:	DisplayBoneyardOptions

Purpose:		This function displays the options for the human player after picking a boneyard tile.
				This option is only showed if there is no orphan double train and there is a valid tile that
				can be played in one of these trains.

Parameters:

Return Value:
				char that represents one of the train.
Algorithm:

				none.

Assistance Received: none
********************************************************************* */
char User::DisplayBoneyardOptions()
{
	//char value where the options input is stored
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

/* *********************************************************************
Function Name:	BoneyardTilePlayable

Purpose:		This function checks if the boneyard tile is playable for the human player.

Parameters:
				1)  a_tile --> boneyard tile that was picked.
				2)	a_trainslist[] -->pointer to the pointers array of train object
			
Return Value:
				boolean --> true if boneyard tile is playable to one of the trains, false otherwise.
Algorithm:
				-Check usertrain back tile to find if boneyard tile can be placed
				-Check if computer train is marked
					- if yes, Check computertrain back tile to find if boneyard tile can be placed
				-Check mexican train back tile to find if boneyard tile can be placed

Assistance Received: none
********************************************************************* */
bool User::BoneyardTilePlayable(Tile a_tile, Train* a_trainslist[])
{
	//tile of the user train where player tiles can be added
	Tile usertrainback = (**a_trainslist).GetAllTiles().back();
	
	if (usertrainback.GetSide2() == a_tile.GetSide1() || usertrainback.GetSide2() == a_tile.GetSide2()) {
		return true;
	}

	Tile computertrainback = (**(a_trainslist+1)).GetAllTiles().back();

	if ((**(a_trainslist + 1)).isTrainMarked()) {
		if (computertrainback.GetSide2() == a_tile.GetSide1() || computertrainback.GetSide2() == a_tile.GetSide2()) {
			return true;
		}

	}
	
	Tile mexicantrainback = (**(a_trainslist + 2)).GetAllTiles().back();
	if (mexicantrainback.GetSide2() == a_tile.GetSide1() || mexicantrainback.GetSide2() == a_tile.GetSide2()) {
		return true;
	}

	return false;
}



/* *********************************************************************
Function Name:	CheckandPlacesecDouble

Purpose:		This function checks if the tile chosen after playing one double tile is playable or not. If so places
				the tile on chosen train and returns a boolean true value.

Parameters:
				1)	a_trainslist[] -->pointer to the pointers array of train object
				2) a_chosentrain --> train where second double tile is about to be placed
				3) a_replay --> boolean that represents if the user can play one more move continously.
				4) a_validtile --> boolean that represents if the player has made a move to complete his turn.
				5) a_player --> string value of the name of the train where tile is to be moved.


Return Value:
				boolean --> true if second double can be played, false otherwise.
Algorithm:
				if tile is not double 
					- go and move the tile to chosen train
				if tile is a double
					- check if that tiles meets the requirement of valid second double
					- if it doesnot meet requirements display message and return false. 

Assistance Received: none
********************************************************************* */
bool User::CheckandPlacesecDouble(Train* a_trainslist[], Train& a_chosenTrain, bool& a_replay, bool& a_validtile, string a_train)
{
	//tilenumber to play
	int tile_number = GetValidTile();
	//represents if tile can be placed or not
	bool placement_possible = false;
	//tile chosen by the user.
	Tile userinput = GetTile(tile_number - 1);

	//if player doesnot choose double tile for the second time
	if (userinput.GetSide1() != userinput.GetSide2()) {
		PlaceCustomTiletoTrain(a_chosenTrain, a_replay, a_validtile, a_train, tile_number);
		placement_possible = true;
	}
	//if it is a double tile for second turn
	else {
		//if a train matches a double tile.
		if (a_chosenTrain.GetTop().GetSide2() == userinput.GetSide1() || a_chosenTrain.GetTop().GetSide2() == userinput.GetSide1()) {

			//CheckifvalidTileispresent
			bool double_tile_is_valid = ValidsecondDouble(a_trainslist, a_chosenTrain, userinput);
			if (double_tile_is_valid) {
				PlaceCustomTiletoTrain(a_chosenTrain, a_replay, a_validtile, a_train, tile_number);
				a_replay = true;
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


/* *********************************************************************
Function Name:	PlaceCustomTiletoTrain

Purpose:		This function helps to move the specified tile number to the specified train.

Parameters:
				1)	a_train--> train where tile is to be placed passed by reference
				2) a_replay --> boolean that represents if the user can play one more move continously.
				3) a_validtile --> boolean that represents if the player has made a move to complete his turn.
				4) a_trainname --> string value of the name of the train where tile is to be moved.
				5) a_tilenumber --> position of tile in the tiles list.

Return Value:
				none
Algorithm:
				Check if tile can be placed on the train using checkTrainMove function.
				- if playable
					- if double tile modify a_replay to true so user gets one more turn
				-if not playable
					-display message to show tile cannot be moved.
			

Assistance Received: none
********************************************************************* */
void User::PlaceCustomTiletoTrain(Train& a_train, bool& a_replay, bool& a_validtile, string a_trainname, int a_tilenumber)
{
	//using the last tile of the player list which is the boneyard tile.
	//int tilenumber = GetPlayerTiles().size();
	int tilenumber = a_tilenumber;
	Tile nextmove = GetPlayerTiles().at(tilenumber - 1);
	//Check TrainMove check if the move to the Train is valid or not and returns true if the 
	//move was successful.
	if (CheckTrainMove(a_train, nextmove, tilenumber)) {
		//this gives one extra chance in condition of OrphanDouble
		if (nextmove.GetSide1() == nextmove.GetSide2()) {
			a_replay = true;
		}
		a_validtile = true;
		//only work if the train type is User or computer 
		//traintype.RemoveMark();
	}
	else
	{
		cout << "The tile you chose cannot be placed on the " + a_trainname + " train " << endl;

	}
}


/* *********************************************************************
Function Name:	PlaceCustomTiletoTrain

Purpose:		Allows user to input tile number to play and tries to place the chosen tile to the train.

Parameters:
				1)	a_train--> train where tile is to be placed passed by reference
				2) a_replay --> boolean that represents if the user can play one more move continously.
				3) a_validtile --> boolean that represents if the player has made a move to complete his turn.
				4) a_trainname --> string value of the name of the train where tile is to be moved.
			

Return Value:
				none
Algorithm:
				-Ask for the user to enter a tilenumber to play on the chosen train
				-Check if tile can be placed on the train using checkTrainMove function.
				- if playable
					- if double tile modify a_replay to true so user gets one more turn
				-if not playable
					-display message to show tile cannot be moved.


Assistance Received: none
********************************************************************* */
void User::PlaceTiletoTrain(Train& a_train, bool& a_replay, bool& a_validtile, string a_trainname)
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
	if (CheckTrainMove(a_train, nextmove, tilenumber)) {
		//this gives one extra chance in condition of OrphanDouble
		if (nextmove.GetSide1() == nextmove.GetSide2()) {
			a_replay = true;
		}
		a_validtile = true;
	}
	else
	{
		cout << "The tile you chose cannot be placed on the " + a_trainname + " train " << endl;

	}

}


/* *********************************************************************
Function Name:	Displayoptions

Purpose:		This function helps to display options to the human player to make the moves.
				After the value is returned if the input is not validated this function is called again.

Parameters:
				none

Return Value:
				char value which decides the next move
Algorithm:		
				none

Assistance Received: none
********************************************************************* */
char User::Displayoptions()
{
	//this stores the user input for all the options
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


/* *********************************************************************
Function Name:	GetValidTile

Purpose:		This function allows the user to choose a tile number to play on a train. It also
				validates the tilenumber and if invalid asks user to enter the number again.

Parameters:
				none

Return Value:
				integer value which is the tile number to be played.
Algorithm:
				none

Assistance Received: https://stackoverflow.com/questions/5864540/infinite-loop-with-cin-when-typing-string-while-a-number-is-expected
********************************************************************* */
int User::GetValidTile()
{	
	//tilenumber to be returned back
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