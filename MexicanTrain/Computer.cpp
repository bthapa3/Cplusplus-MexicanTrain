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
			1) trainslist  --> pointer to the pointers array of train object
			2) boneyard    --> vector of boneyard tiles passed with reference
			3) continuedmove  --> integer value that tells the number of times user has played prior moves without alternating.
			4) quit --> boolean value that is set to true when user want to serialize and quit.
Return Value: 
			returns a boolean value that states if the user played a double tile.

Local Variables: None
Algorithm: Loop through mHandPile vector and display the card
Assistance Received: None
********************************************************************* */
bool Computer::PlayMove(Train* trainslist[], vector<Tile>& boneyard,int continuedmove, bool & quit)
{
	
	string check = "X";
	if (continuedmove > 0) {
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
			quit = true;
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
	if (continuedmove == 0 && OrphanDoublePresent(trainslist, traintype)) {
		//move to the orphan double train as needed.
		if (traintype == 'U' && (checkOrphanandMove(trainslist, **trainslist))) return turn_repeat;
		if (traintype == 'M' && (checkOrphanandMove(trainslist, **(trainslist+2)))) return turn_repeat;
		if (traintype == 'C' && (checkOrphanandMove(trainslist, **(trainslist + 1)))) return turn_repeat;
		
		cout << "Computer didnot have any tiles to play for orphan double train so boneyard tile was added:" << boneyard.at(0).GetSide1() << "-" << boneyard.at(0).GetSide2() << endl;
		
		//if tile was present on boneyard and picked try to place on the user train.
		if (PickBoneyard(boneyard, **(trainslist + 1))) {
			BoneyardtoTrain(trainslist, turn_repeat);
			return turn_repeat;
		}
		else {
			cout << "Boneyard had no tiles. so computer train is just marked." << endl;
			
		}
		DisplayandContinue();
		return turn_repeat;

	}

	//ERRORS: souble tile can be placed without giving double train if computer detects orphan double is not going to be valid.needs setrepeating.


	//checks if the mexican train is empty if so adds tile if available.
	if (StartMexicanTrain(trainslist, tilenumber, train)) {
		DisplayTileMove(tilenumber, train, "it started the mexican train");
		MoveTiletoTrain(trainslist, tilenumber, train);
		return turn_repeat;
	}

	// second argument **trainslist is the train of the opponent player as current player is computer.
	if (Playopponenttrain(trainslist, **(trainslist), tilenumber, train)) {
		DisplayTileMove(tilenumber, train, "the opponent train had marker");
		SetRepeating(turn_repeat, tilenumber);
		MoveTiletoTrain(trainslist, tilenumber, train);
		return turn_repeat;
	}


	//check if you can force other player to play orphan double train & orphan double cannot be played more than two times.
	//continued move value is 0 and 1 for first two times.
	if (PlayOrphanDoublemove(trainslist, tilenumber, train, **trainslist)  && continuedmove<2 ) {
		Tile mytile = GetPlayerTiles().at(tilenumber - 1);
		if ((continuedmove==0) || (continuedmove == 1 && ValidsecondDouble(trainslist, train,mytile) )) {
			DisplayTileMove(tilenumber, train, "it forces opponent to play orphan double train");
			SetRepeating(turn_repeat, tilenumber);
			MoveTiletoTrain(trainslist, tilenumber, train);
			return turn_repeat;
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

	bool can_playself = PlaySelfTrain(trainslist, tilenumber, **(trainslist + 1));
	if (can_playself) {
		selftile = tilenumber;
		selfsum = GetPlayerTiles().at(tilenumber - 1).GetSide1() + GetPlayerTiles().at(tilenumber - 1).GetSide2();
		selftrain = **(trainslist + 1);
	}

	//if the computer played double tile before on the computer or mexican train try not to play itself
	// if computer played double tile on user train still will try to play on opponent train as per winning strategy.
	//continued move means the user has played a double tile before.
	if (continuedmove == 1) {
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


	if (((can_playmexican && can_playself) && selfsum >= mexicansum) || (can_playself && !can_playmexican)) {

		DisplayTileMove(selftile, **(trainslist + 1), "it is the largest possible tile to play");
		SetRepeating(turn_repeat, selftile);
		MoveTiletoTrain(trainslist, selftile, **(trainslist + 1));
		return turn_repeat;

	}
	else if (((can_playmexican && can_playself) && selfsum < mexicansum) || (!can_playself && can_playmexican)) {

		DisplayTileMove(mexicantile, **(trainslist + 2), "it is the largest possible tile to play");
		SetRepeating(turn_repeat, mexicantile);
		MoveTiletoTrain(trainslist, mexicantile, mexicantrain);
		return turn_repeat;
	}
	else {
		cout << "Computer didnot have any tiles to play so boneyard tile was added to tiles list" << endl;
		cout << "Tile added:" << boneyard.at(0).GetSide1() << "-" << boneyard.at(0).GetSide2() << endl;
		//if tile was present on boneyard and picked try to place on the user train.
		if (PickBoneyard(boneyard, **(trainslist + 1))) {
			BoneyardtoTrain(trainslist, turn_repeat);
			return turn_repeat;
		}
		else {
			cout << "boneyard had no tiles. so just train is marked." << endl;
			
		}
		
		DisplayandContinue();
		return turn_repeat;

	}		
}


void Computer::BoneyardtoTrain(Train* trainslist[], bool& replay)
{
	Tile last_tile = GetPlayerTiles().at(GetPlayerTiles().size() - 1);
	char train;
	if (OrphanDoublePresent(trainslist, train)) {
		if (train == 'U') {
			if (CanPlayinTrain(**trainslist)) {
				int tile_number = GetPlayableTile(**trainslist);
				SetRepeating(replay, tile_number);
				DisplayTileMove(tile_number, **trainslist, "boneyard tile matched with orphan double train");
				MoveTiletoTrain(trainslist, tile_number, **trainslist);
				return;
				
			}
			else {
				DisplayandContinue();
			}
		}
		else if (train == 'C') {
			if (CanPlayinTrain(**(trainslist+1))) {
				int tile_number = GetPlayableTile(**(trainslist+1));
				SetRepeating(replay, tile_number);
				DisplayTileMove(tile_number, **(trainslist + 1), "boneyard tile matched with orphan double train");
				MoveTiletoTrain(trainslist, tile_number, **(trainslist+1));
				return;
			}
			else {
				DisplayandContinue();
			}
		}
		else if (train == 'M') {
			if (CanPlayinTrain(**(trainslist+2))) {
				int tile_number = GetPlayableTile(**(trainslist+2));
				SetRepeating(replay, tile_number);
				DisplayTileMove(tile_number, **(trainslist + 2), "boneyard tile matched with orphan double train");
				MoveTiletoTrain(trainslist, tile_number, **(trainslist+2));
				return;
			}
			else {
				DisplayandContinue();
			}
		}
	}
	else {
		//priority player train
		if ((**trainslist).isTrainMarked() && CanPlayinTrain(**trainslist)) {
			int tile_number = GetPlayableTile(**trainslist);
			SetRepeating(replay, tile_number);
			DisplayTileMove(tile_number, **trainslist, "boneyard tile matched with opponent train");
			MoveTiletoTrain(trainslist, tile_number, **trainslist);
			return;

		}
		// than play mexican train
		else if (CanPlayinTrain(**(trainslist + 2))) {
			int tile_number = GetPlayableTile(**(trainslist + 2));
			SetRepeating(replay, tile_number);
			DisplayTileMove(tile_number, **(trainslist + 2), "boneyard tile matched with mexican train");
			MoveTiletoTrain(trainslist, tile_number, **(trainslist + 2));
			return;
		}
		//play own train at the end
		else if (CanPlayinTrain(**(trainslist + 1))) {
			int tile_number = GetPlayableTile(**(trainslist + 1));
			SetRepeating(replay, tile_number);
			DisplayTileMove(tile_number, **(trainslist + 1), "boneyard tile matched with self train");
			MoveTiletoTrain(trainslist, tile_number, **(trainslist + 1));
			return;
		}
		else {
			cout << "The boneyard train doesnot match any train so could not be placed anywhere!" << endl;
			DisplayandContinue();
		}
	}
}

bool Computer::checkOrphanandMove(Train * trainslist[],Train& train)
{
	
	if (CanPlayinTrain(train)) {

		int tilenumber = GetPlayableTile(train);
		DisplayTileMove(tilenumber, train, "it was the orphan double train");
		MoveTiletoTrain(trainslist, tilenumber,train);
		return true;
	}	
}

void Computer::DisplayandContinue()
{
	string dummyin;
	cout << "Press any key to continue" << endl;
	cin >> dummyin;
}

void Computer::DisplayTileMove(int tilenumber, Train train, string goal)
{
	string tile = to_string(GetPlayerTiles().at(tilenumber - 1).GetSide1()) + '-' + to_string(GetPlayerTiles().at(tilenumber - 1).GetSide2());
	string trainname = train.trainType();
	cout << "Tile: " << tile << " was moved to the " << trainname << " as " << goal << endl;
	cout << "---------------------------------------------------------------------------------" << endl;
	cout << "Enter y to continue>>";
	string dummyinput;
	cin >> dummyinput;


}

void Computer::SetRepeating(bool& replay, int tilenumber)
{
	if (GetPlayerTiles().at(tilenumber - 1).GetSide1() == GetPlayerTiles().at(tilenumber - 1).GetSide2()) {
		replay = true;
	}
	return;
}


void Computer::MoveTiletoTrain(Train* trainslist[], int tilenumber, Train train)
{
	Tile tiletoadd = GetPlayerTiles().at(tilenumber - 1);
	//here train type is checked because we cannot modify on the copy of the train object.
	if (train.trainType() == "usertrain") {
		CheckTrainMove(**trainslist, tiletoadd, tilenumber);

	}
	else if (train.trainType() == "computertrain") {
		CheckTrainMove(**(trainslist + 1), tiletoadd, tilenumber);
		//since computer player is the only player using this function removing mark from here works.
		(**(trainslist + 1)).RemoveMark();

	}
	else if (train.trainType() == "mexicantrain") {
		CheckTrainMove(**(trainslist + 2), tiletoadd, tilenumber);
	}
	else {
		cout << "train type is: " << train.trainType() << endl;
	}
}