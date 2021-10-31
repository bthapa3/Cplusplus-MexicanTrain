/*
************************************************************
* Name:  Bishal Thapa									   *
* Project:  Project 1 Mexican Train C++				       *
* Class:  CMPS366 OPL				                       *
* Date:  09/27/2020				                           *
************************************************************
*/

#include "Computer.h"


/* *********************************************************************
Function Name: PlayMove
Purpose: To proceed to the next move of the computer

Parameters: 
			1) a_trainslist  --> pointer to the pointers array of train object
			2) a_boneyard    --> vector of boneyard tiles passed with reference
			3) a_continuedmove  --> integer value that tells the number of times user has played prior moves without alternating.
			4) a_quit --> boolean value that is set to true when user want to serialize and quit.

Return Value: 
			returns a boolean value that states if the user played a double tile.

Algorithm: If orphan train present and this is not a continous second turn:
					- Check if can play orphan double train and suggest tile
					- If not suggest to pick boneyard tile
				else-
					-if playing for first time try to start mexican train
					-try to play orphan double train
					-try to play opponent train
					-if a double tile played before avoid playing on same train
					-try playing biggest tile on one of computer or mexican train
					-pick tile from boneyard
			
Assistance Received: None
********************************************************************* */
bool Computer::PlayMove(Train* trainslist[], vector<Tile>& a_boneyard,int a_continuedmove, bool & a_quit)
{
	//check stores a char value and checks everytime if user want to continue or serialize
	string check = "X";
	if (a_continuedmove > 0) {
		cout << "Since computer played a double tile, computer gets one more play." << endl;
	}
	while (check != "S" && check != "C") {
		cout << "Next Player: Computer:" << endl;
		cout << "-------------------------------------------------------------------------" << endl;
		cout << "Do you want to serialize and quit before Computer turn?" <<endl;
		cout << "Press (S) to serialize and Quit"<<endl; 
		cout << "Press (C) to continue playing" << endl;
		cout << "-------------------------------------------------------------------------" << endl;
		cout << ">>";
		cin >> check;
		if (check == "S") {
			a_quit = true;
			return false;
		}
	}
	//returns if the strategy gave one extra move to the user.
	//bool replay  = WinningStrategy(trainslist,boneyard, continuedmove );
	//return replay;
	//get all the end of the tiles of the train to get the winning strategy
	int tilenumber;
	Train train;
	bool turn_repeat = false;
	char traintype;

	//check if there is a orphan double train present
	if (a_continuedmove == 0 && OrphanDoublePresent(trainslist, traintype)) {
		//move to the orphan double train as needed.
		if (traintype == 'U' && (checkOrphanandMove(trainslist, **trainslist))) return turn_repeat;
		if (traintype == 'M' && (checkOrphanandMove(trainslist, **(trainslist+2)))) return turn_repeat;
		if (traintype == 'C' && (checkOrphanandMove(trainslist, **(trainslist + 1)))) return turn_repeat;
		
		cout << "Computer didnot have any tiles to play for orphan double train so boneyard tile was added:" << a_boneyard.at(0).GetSide1() << "-" << a_boneyard.at(0).GetSide2() << endl;
		
		//if tile was present on boneyard and picked try to place on the user train.
		if (PickBoneyard(a_boneyard, **(trainslist + 1))) {
			BoneyardtoTrain(trainslist, turn_repeat);
			return turn_repeat;
		}
		else {
			cout << "Boneyard had no tiles. so computer train is just marked." << endl;
			
		}
		DisplayandContinue();
		return turn_repeat;

	}


	//checks if the mexican train is empty if so adds tile if available.
	if (StartMexicanTrain(trainslist, tilenumber, train)) {
		DisplayTileMove(tilenumber, train, "it started the mexican train");
		MoveTiletoTrain(trainslist, tilenumber, train);
		return turn_repeat;
	}


	//check if you can force other player to play orphan double train & orphan double cannot be played more than two times.
	//continuedmove value is 0 and 1 for first two times.
	if (PlayOrphanDoublemove(trainslist, tilenumber, train, **trainslist)  && a_continuedmove<2 ) {
		Tile mytile = GetPlayerTiles().at(tilenumber - 1);
		if ((a_continuedmove==0) || (a_continuedmove == 1 && ValidsecondDouble(trainslist, train,mytile) )) {
			DisplayTileMove(tilenumber, train, "it forces opponent to play orphan double train");
			SetRepeating(turn_repeat, tilenumber);
			MoveTiletoTrain(trainslist, tilenumber, train);
			return turn_repeat;
		}
	}

	// second argument **trainslist is the train of the opponent player as current player is computer.
	if (Playopponenttrain(trainslist, **(trainslist), tilenumber, train)) {
		DisplayTileMove(tilenumber, train, "the opponent train had marker");
		SetRepeating(turn_repeat, tilenumber);
		MoveTiletoTrain(trainslist, tilenumber, train);
		return turn_repeat;
	}


	int mexicantile, mexicansum, selftile, selfsum;
	Train mexicantrain, selftrain;

	bool can_playmexican = PlayMexicanTrain(trainslist, tilenumber, train);
	if (can_playmexican) {
		mexicantile = tilenumber;
		mexicansum = GetPlayerTiles().at(tilenumber - 1).GetSide1() + GetPlayerTiles().at(tilenumber - 1).GetSide2();
		mexicantrain = train;
	}

	bool can_playself = PlaySelfTrain(trainslist, tilenumber, **(trainslist + 1));
	if (can_playself) {
		selftile = tilenumber;
		selfsum = GetPlayerTiles().at(tilenumber - 1).GetSide1() + GetPlayerTiles().at(tilenumber - 1).GetSide2();
		selftrain = **(trainslist + 1);
	}

	//if the computer played double tile before on the computer or mexican train try not to play itself
	// if computer played double tile on user train still will try to play on opponent train as per winning strategy.
	//continued move means the user has played a double tile before.
	if (a_continuedmove == 1) {
		OrphanDoublePresent(trainslist, traintype);
		if (traintype == 'C' && can_playmexican) {
			DisplayTileMove(mexicantile, **(trainslist + 2), "it is the largest possible tile to play and helps for orphan double");
			MoveTiletoTrain(trainslist, mexicantile, mexicantrain);
			return turn_repeat;
		}
		else if (traintype == 'M' && can_playself) {
			DisplayTileMove(selftile, **(trainslist + 1), "it is the largest possible tile to play and helps for orphan double");
			MoveTiletoTrain(trainslist, selftile, **(trainslist + 1));
			return turn_repeat;
		}
	}

	//calculates the sum of tiles and plays on the train where sum is bigger.
	if (((can_playmexican && can_playself) && selfsum >= mexicansum) || (can_playself && !can_playmexican)) {

		DisplayTileMove(selftile, **(trainslist + 1), "it is the largest possible tile to play");
		SetRepeating(turn_repeat, selftile);
		MoveTiletoTrain(trainslist, selftile, **(trainslist + 1));
		return turn_repeat;

	}

	//calculates the sum of tiles and plays on the train where sum is bigger.
	else if (((can_playmexican && can_playself) && selfsum < mexicansum) || (!can_playself && can_playmexican)) {

		DisplayTileMove(mexicantile, **(trainslist + 2), "it is the largest possible tile to play");
		SetRepeating(turn_repeat, mexicantile);
		MoveTiletoTrain(trainslist, mexicantile, mexicantrain);
		return turn_repeat;
	}

	//if none of the trains are playable
	else {
		cout << "Computer didnot have any tiles to play so boneyard tile was added to tiles list" << endl;
		cout << "Tile added:" << a_boneyard.at(0).GetSide1() << "-" << a_boneyard.at(0).GetSide2() << endl;
		//if tile was present on boneyard and picked try to place on the user train.
		if (PickBoneyard(a_boneyard, **(trainslist + 1))) {
			BoneyardtoTrain(trainslist, turn_repeat);
			return turn_repeat;
		}
		else {
			cout << "Boneyard had no tiles. so just train is marked." << endl;
			
		}
		
		//this is just for pausing and displaying last move to user. 
		DisplayandContinue();
		return turn_repeat;
	}		
}


/* *********************************************************************
Function Name: BoneyardtoTrain
Purpose: To move the tile picked from the boneyard by the user to a valid train.
Parameters:
			1) a_trainslist  --> pointer to the pointers array of train object
			2) a_replay --> boolean value that states if a user gets another turn to play in case of double tile.

Return Value:
			none

Algorithm: 
			If Orphan double train is present check if boneyard tile can be placed there. If no 
			orphan double train try to place on the trains in the order opponent train, mexican train,
			self train.

Assistance Received: None
********************************************************************* */

void Computer::BoneyardtoTrain(Train* a_trainslist[], bool& a_replay)
{
	Tile last_tile = GetPlayerTiles().at(GetPlayerTiles().size() - 1);
	char train;
	if (OrphanDoublePresent(a_trainslist, train)) {
		if (train == 'U') {
			if (CanPlayinTrain(**a_trainslist)) {
				int tile_number = GetPlayableTile(**a_trainslist);
				SetRepeating(a_replay, tile_number);
				DisplayTileMove(tile_number, **a_trainslist, "boneyard tile matched with orphan double train");
				MoveTiletoTrain(a_trainslist, tile_number, **a_trainslist);
				return;
				
			}
			else {
				DisplayandContinue();
			}
		}
		else if (train == 'C') {
			if (CanPlayinTrain(**(a_trainslist+1))) {
				int tile_number = GetPlayableTile(**(a_trainslist+1));
				SetRepeating(a_replay, tile_number);
				DisplayTileMove(tile_number, **(a_trainslist + 1), "boneyard tile matched with orphan double train");
				MoveTiletoTrain(a_trainslist, tile_number, **(a_trainslist+1));
				return;
			}
			else {
				DisplayandContinue();
			}
		}
		else if (train == 'M') {
			if (CanPlayinTrain(**(a_trainslist+2))) {
				int tile_number = GetPlayableTile(**(a_trainslist+2));
				SetRepeating(a_replay, tile_number);
				DisplayTileMove(tile_number, **(a_trainslist + 2), "boneyard tile matched with orphan double train");
				MoveTiletoTrain(a_trainslist, tile_number, **(a_trainslist+2));
				return;
			}
			else {
				DisplayandContinue();
			}
		}
	}
	else {
		//priority player train(opponent)
		if ((**a_trainslist).isTrainMarked() && CanPlayinTrain(**a_trainslist)) {
			int tile_number = GetPlayableTile(**a_trainslist);
			SetRepeating(a_replay, tile_number);
			DisplayTileMove(tile_number, **a_trainslist, "boneyard tile matched with opponent train");
			MoveTiletoTrain(a_trainslist, tile_number, **a_trainslist);
			return;

		}
		// than play mexican train
		else if (CanPlayinTrain(**(a_trainslist + 2))) {
			int tile_number = GetPlayableTile(**(a_trainslist + 2));
			SetRepeating(a_replay, tile_number);
			DisplayTileMove(tile_number, **(a_trainslist + 2), "boneyard tile matched with mexican train");
			MoveTiletoTrain(a_trainslist, tile_number, **(a_trainslist + 2));
			return;
		}
		//play computer train at the end(self train)
		else if (CanPlayinTrain(**(a_trainslist + 1))) {
			int tile_number = GetPlayableTile(**(a_trainslist + 1));
			SetRepeating(a_replay, tile_number);
			DisplayTileMove(tile_number, **(a_trainslist + 1), "boneyard tile matched with self train");
			MoveTiletoTrain(a_trainslist, tile_number, **(a_trainslist + 1));
			return;
		}
		else {
			cout << "The boneyard train doesnot match any train so could not be placed anywhere!" << endl;
			DisplayandContinue();
		}
	}
}

/* *********************************************************************
Function Name: checkOrphanandMove
Purpose: To check if any tile can be placed on the orphan double train

Parameters:
			1) a_trainslist  --> pointer to the pointers array of train object
			2) a_train --> Orphan Double train where tile is to be placed.

Return Value:
			returns a boolean value if the tiles was placed , false otherwise.

Algorithm:
			Check if any of the player's tiles can be placed on the orphan double train.
			If tile found, move it to the train and display information regarding that.

Assistance Received: None
********************************************************************* */

bool Computer::checkOrphanandMove(Train * a_trainslist[],Train& a_train)
{
	
	if (CanPlayinTrain(a_train)) {

		int tilenumber = GetPlayableTile(a_train);
		DisplayTileMove(tilenumber, a_train, "it was the orphan double train");
		MoveTiletoTrain(a_trainslist, tilenumber,a_train);
		return true;
	}	
}

/* *********************************************************************
Function Name:	DisplayandContinue
Purpose: it takes dummy input to allows users to read the changes and continue

Parameters:
			none

Return Value:
			none

Algorithm:
			none

Assistance Received: None
********************************************************************* */
void Computer::DisplayandContinue()
{
	string dummyin;
	cout << "Press any key to continue" << endl;
	cin >> dummyin;
}


/* *********************************************************************
Function Name:	DisplayTileMove
Purpose: Display a reasoning, tiles and train whenever a player's tile is moved to a train

Parameters:
			a_tilenumber --> tilenumber of the tile to be moved. Relates to tile number displayed on screen.
			a_train --> Train where the tile is to be moved.
			a_goal --> reasoning behind the move of the tile.

Return Value:
			none

Algorithm:
			none

Assistance Received: None
********************************************************************* */
void Computer::DisplayTileMove(int a_tilenumber, Train a_train, string a_goal)
{
	string tile = to_string(GetPlayerTiles().at(a_tilenumber - 1).GetSide1()) + '-' + to_string(GetPlayerTiles().at(a_tilenumber - 1).GetSide2());
	string trainname = a_train.trainType();
	cout << "Tile: " << tile << " was moved to the " << trainname << " as " << a_goal << endl;
	cout << "---------------------------------------------------------------------------------" << endl;
	cout << "Enter y to continue>>";
	string dummyinput;
	cin >> dummyinput;


}


/* *********************************************************************
Function Name:	SetRepeating
Purpose: 
				Modify the replay varaible value to allow the user to play a tile twice in case double tile exists.

Parameters:
			a_tilenumber --> tilenumber of the tile to be moved. Relates to tile number displayed on screen.
			a_replay --> variable that holds boolean value which states if player gets to play again

Return Value:
			none

Algorithm:
			if tile is a double tile set replay to true.

Assistance Received: None
********************************************************************* */
void Computer::SetRepeating(bool& a_replay, int a_tilenumber)
{
	if (GetPlayerTiles().at(a_tilenumber - 1).GetSide1() == GetPlayerTiles().at(a_tilenumber - 1).GetSide2()) {
		a_replay = true;
	}
	return;
}



/* *********************************************************************
Function Name:	MoveTiletoTrain
Purpose:		Move a given computer tile with tilenumber to a given train.

Parameters:
			1) a_trainslist  --> pointer to the pointers array of train object
			2) a_tilenumber --> position of tile on the tile list that relates to the value displayed on the screen.
			3) a_train --> train where the tile is to be moved.

Return Value:
			none

Algorithm:
			move tile to the train. If the train is computer train and there is a marker placed 
			remove marker.

Assistance Received: None
********************************************************************* */
void Computer::MoveTiletoTrain(Train* a_trainslist[], int a_tilenumber, Train a_train)
{
	Tile tiletoadd = GetPlayerTiles().at(a_tilenumber - 1);
	//here train type is checked because we cannot modify on the copy of the train object.
	if (a_train.trainType() == "usertrain") {
		CheckTrainMove(**a_trainslist, tiletoadd, a_tilenumber);

	}
	else if (a_train.trainType() == "computertrain") {
		CheckTrainMove(**(a_trainslist + 1), tiletoadd, a_tilenumber);
		//since computer player is the only player using this function removing mark from here works.
		(**(a_trainslist + 1)).RemoveMark();

	}
	else if (a_train.trainType() == "mexicantrain") {
		CheckTrainMove(**(a_trainslist + 2), tiletoadd, a_tilenumber);
	}
	else {
		cout << "train type is: " << a_train.trainType() << endl;
	}
}