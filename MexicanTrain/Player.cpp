#include "Player.h"



void Player::addtile(Tile tile)
{
	tileslist.push_back(tile);
}

bool Player::CheckTrainMove(Train & Train, Tile tile, int tilenumber)
{
	//moving a user chosen tile to a Player train
	if (tile.GetSide1() == Train.GetAllTiles().back().GetSide2() || tile.GetSide2() == Train.GetAllTiles().back().GetSide2())
	{

		//if this is a double tile next tile is flipped accordingly
		if (Train.GetAllTiles().back().GetSide1() == Train.GetAllTiles().back().GetSide2()  && 
			(tile.GetSide1() != Train.GetAllTiles().back().GetSide2())) 
		{
			tile.Filpside();
		}
		//two consecutive tiles are flipped in order to set matching number to each other.
		else if ((Train.GetAllTiles().back().GetSide1() != Train.GetAllTiles().back().GetSide2()) && 
			tile.GetSide1() == Train.GetAllTiles().back().GetSide1() || tile.GetSide2() == Train.GetAllTiles().back().GetSide2()) 
		{
			tile.Filpside();
		}
		//adds tile to the Train
		Train.Addtile(tile);
		//removes tile from the user or computer's tile pile.
		RemoveTile(tilenumber - 1);
		return true;
	}
	else
	{
		return false;

	}	
}

void Player::RemoveTile(int position)
{
	tileslist.erase(tileslist.begin() + position);
}



bool Player::OrphanDoublePresent(Train * trainslist[], char & train)
{
	
	if ( (**(trainslist)).GetAllTiles().size()>1 && (**(trainslist)).GetTop().GetSide1() == (**(trainslist)).GetTop().GetSide2()) {
		train= 'U';
		return true;
	}
	else if ((**(trainslist+1)).GetAllTiles().size()>1 && (**(trainslist+1)).GetTop().GetSide1() == (**(trainslist+1)).GetTop().GetSide2()) {
		train= 'C';
		return true;
	}
	else if ((**(trainslist+2)).GetAllTiles().size()>1 && (**(trainslist+2)).GetTop().GetSide1() == (**(trainslist+2)).GetTop().GetSide2()) {
		train= 'M';
		return true;
	}
	return false;
}



bool Player::Mainmove(Train * trainslist[], vector<Tile>& boneyard, int continuedplay) {
	
	//cout << "This is the main move" << endl;
	
	bool replay= PlayMove( trainslist, boneyard, continuedplay);


	return replay;

}

void Player::WinningStrategy(Train * trainslist[], vector<Tile>& boneyard)
{
	//get all the end of the tiles of the train to get the winning strategy
    Train traintoplay;
	Tile tiletoplay;
	int tilenumber;
	Train train;


	if (StartMexicanTrain(trainslist, tilenumber, train)) {
		cout << "Mexican train has been started by computer player." << endl;
		cout << "Tiles Played: " << GetPlayerTiles().at(tilenumber-1).GetSide1() << "-" << GetPlayerTiles().at(tilenumber-1).GetSide2() << endl;
		cout << "-----------------------------------------------------------------" << endl;
		MoveTiletoTrain(trainslist, tilenumber, train);
		string dummyin;
		cout << "Press y to continue to players turn" << endl;
		cin >> dummyin;
		return;
	}
	// second argument **trainslist is the train of the opponent player as current player is computer.
	if (Playopponenttrain(trainslist, **(trainslist),  tilenumber, train)) {
		cout << "Since the opponent train had a marker a tile was played" << endl;
		cout << "Tiles Played: " << GetPlayerTiles().at(tilenumber - 1).GetSide1() << "-" << GetPlayerTiles().at(tilenumber - 1).GetSide2() << endl;
		cout << "-----------------------------------------------------------------" << endl;
		MoveTiletoTrain(trainslist, tilenumber, train);
		string dummyin;
		cout << "Press any key to continue" << endl;
    	cin >> dummyin;
		return;
	}

	//check if you can force other player to play orphan double train
	if (PlayOrphanDoublemove(trainslist, tilenumber, train, **trainslist)) {
		cout << "Computer train played a double tile." << endl;
		cout << "Tiles Played: " << GetPlayerTiles().at(tilenumber - 1).GetSide1() << "-" << GetPlayerTiles().at(tilenumber - 1).GetSide2() << endl;
		cout << "-----------------------------------------------------------------" << endl;
		MoveTiletoTrain(trainslist, tilenumber, train);
		string dummyin;
		cout << "Press any key to continue" << endl;
		cin >> dummyin;
		return;
	}


	
	
	
	//check if you can play to the mexican train
	if (PlayMexicanTrain(trainslist, tilenumber, train)) {
		cout << "Computer trained placed tilenumber: "<< tilenumber  <<"to the mexican train" << endl;
		cout << "Tiles Played: " << GetPlayerTiles().at(tilenumber - 1).GetSide1() << "-" << GetPlayerTiles().at(tilenumber - 1).GetSide2() << endl;
		cout << "-----------------------------------------------------------------" << endl;
		MoveTiletoTrain(trainslist, tilenumber, train);
		string dummyin;
		cout << "Press any key to continue" << endl;
		cin >> dummyin;
		return;
	}

	//check if you can play to the mexican train
	if (PlaySelfTrain(trainslist, tilenumber, **(trainslist+1))) {
		cout << "Computer trained placed tilenumber: " << tilenumber << "to the computer train" << endl;
		cout << "Tiles Played: " << GetPlayerTiles().at(tilenumber - 1).GetSide1() << "-" << GetPlayerTiles().at(tilenumber - 1).GetSide2() << endl;
		cout << "-----------------------------------------------------------------" << endl;
		MoveTiletoTrain(trainslist, tilenumber, **(trainslist+1));
		string dummyin;
		cout << "Press any key to continue" << endl;
		cin >> dummyin;
		return;
	}

	PickBoneyard(boneyard, **(trainslist + 1));


}

bool Player::PlayMove(Train * trainslist[], vector<Tile>& boneyard, int continuedmove)
{
	//This move is made for both players
	//this function doesnot do anything and is a virtual function.
	return false;
}


bool Player::PickBoneyard(vector<Tile> &boneyard, Train & train)
{
	
	//if there is more tiles left
	if (boneyard.size() != 0) {
		Tile boneyardfront = boneyard.front();
		boneyard.erase(boneyard.begin());
		AddtoBack(boneyardfront);
		train.MarkTrain();
		return true;
	}
	// if no tiles left simply mark  the train and pass the turn
	else {
		train.MarkTrain();
		return false;
	}
	
}

int Player::getValidTile()
{
	int tilenumber=0;
	do
	{

		cout << "Enter a tile number that you want to play!";
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
		if (tilenumber > GetPlayerTiles().size() || tilenumber < 1) {
			cout << "Tile number out of range!" << endl;
		}
	} while (tilenumber > GetPlayerTiles().size() || tilenumber < 1);
	return tilenumber;
}



char Player::Displayoptions()
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



void Player::PlaceCustomTiletoTrain(Train& traintype, bool& replay, bool& validtile, string train, int tile_number)
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
			cout << "You get one more chance to play" << endl;
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

void Player::PlaceTiletoTrain(Train& traintype, bool& replay, bool& validtile, string train)
{
	//getting the players tile number input from the user.
	int tilenumber = getValidTile();
	Tile nextmove = GetPlayerTiles().at(tilenumber - 1);



	//Check TrainMove checks if the move to the Train is valid or not and returns true if the 
	//move was successful.
	if (CheckTrainMove(traintype, nextmove, tilenumber)) {
		//this gives one extra chance in condition of OrphanDouble
		if (nextmove.GetSide1() == nextmove.GetSide2()) {
			cout << "You get one more chance to play" << endl;
			replay = true;
		}
		validtile = true;
	}
	else
	{
		cout << "The tile you chose cannot be placed on the " + train + " train " << endl;

	}

}




bool Player::validsecondDouble(Train* trainslist[], Train chosentrain, Tile newtile)
{
	Tile usertrainTop, computertrainTop, mexicantrainTop;
	if (chosentrain.trainType() == "usertrain") {

		usertrainTop = newtile;
		computertrainTop = (**(trainslist + 1)).GetTop();
		mexicantrainTop = (**(trainslist + 2)).GetTop();
	}
	else if (chosentrain.trainType() == "computertrain") {

		usertrainTop = (**trainslist).GetTop();
		computertrainTop = newtile;
		mexicantrainTop = (**(trainslist + 2)).GetTop();
	}
	else {
		usertrainTop = (**trainslist).GetTop();
		computertrainTop = (**(trainslist + 1)).GetTop();
		mexicantrainTop = newtile;
	}

	//checking players have a valid single tile to play after second double.
	for (auto& it : GetPlayerTiles()) {
		if ((it.GetSide1() == usertrainTop.GetSide2() || it.GetSide2() == usertrainTop.GetSide2()) && it.GetSide1() != it.GetSide2()) {
			return true;
		}
	}
	if ((**(trainslist + 1)).isTrainMarked()) {
		for (auto& it : GetPlayerTiles()) {
			if ((it.GetSide1() == computertrainTop.GetSide2() || it.GetSide2() == computertrainTop.GetSide2()) && it.GetSide1() != it.GetSide2()) {
				return true;
			}
		}

	}
	for (auto& it : GetPlayerTiles()) {
		if ((it.GetSide1() == mexicantrainTop.GetSide2() || it.GetSide2() == mexicantrainTop.GetSide2()) && it.GetSide1() != it.GetSide2()) {
			return true;
		}
	}
	return false;


}

void Player::BoneyardtoTrain(Train* trainslist[], bool& replay, bool& validtile)
{
	

}


//this function helps to check if 2 douuble tiles are placeable and returns true if the placement is possible.
bool Player::CheckandPlace(Train* trainslist[], Train& chosenTrain, bool& replay, bool& validtile, string a_player)
{
	int tile_number = getValidTile();
	bool placement_possible = false;
	Tile userinput = gettile(tile_number - 1);

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
			bool double_tile_is_valid = validsecondDouble(trainslist, chosenTrain, userinput);
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

bool Player::CanPlayinTrain(Train train) {

	Tile toptile = train.GetTop();

	for (int i = 0; i < GetPlayerTiles().size(); i++) {
		if (GetPlayerTiles().at(i).GetSide1() == toptile.GetSide2() || GetPlayerTiles().at(i).GetSide2() == toptile.GetSide2()) {
			return true;
		}
	}

	return false;
}



bool Player::CanPlayDouble(Train train)
{
	Tile toptile = train.GetTop();
	for (int i = 0; i < GetPlayerTiles().size(); i++) {
		if ((GetPlayerTiles().at(i).GetSide1() == toptile.GetSide2() || GetPlayerTiles().at(i).GetSide2() == toptile.GetSide2())
		&& (GetPlayerTiles().at(i).GetSide1()== GetPlayerTiles().at(i).GetSide2())) {
			
			return true;
		}
	}
	return false;
}

bool Player::CanPlayNonDouble(Train train)
{
	Tile toptile = train.GetTop();
	for (int i = 0; i < GetPlayerTiles().size(); i++) {
		if ((GetPlayerTiles().at(i).GetSide1() == toptile.GetSide2() || GetPlayerTiles().at(i).GetSide2() == toptile.GetSide2())
			&& (GetPlayerTiles().at(i).GetSide1() != GetPlayerTiles().at(i).GetSide2())) {

			return true;
		}
	}
	return false;
}

int Player::GetPlayableTile(Train train)
{
	Tile toptile = train.GetTop();

	for (int i = 0; i < GetPlayerTiles().size(); i++) {
		if (GetPlayerTiles().at(i).GetSide1() == toptile.GetSide2() || GetPlayerTiles().at(i).GetSide2() == toptile.GetSide2()) {
			return (i+1);
		}
	}

	return -1;
}

int Player::GetPlayableDouble(Train train)
{
	Tile toptile = train.GetTop();
	for (int i = 0; i < GetPlayerTiles().size(); i++) {
		if ((GetPlayerTiles().at(i).GetSide1() == toptile.GetSide2() || GetPlayerTiles().at(i).GetSide2() == toptile.GetSide2())
		&& (GetPlayerTiles().at(i).GetSide1() == GetPlayerTiles().at(i).GetSide2())) {
			return i+1;
		}
	}
	return -1;
}

int Player::GetPlayableNonDouble(Train train)
{
	Tile toptile = train.GetTop();
	for (int i = 0; i < GetPlayerTiles().size(); i++) {
		if ((GetPlayerTiles().at(i).GetSide1() == toptile.GetSide2() || GetPlayerTiles().at(i).GetSide2() == toptile.GetSide2())
			&& (GetPlayerTiles().at(i).GetSide1() != GetPlayerTiles().at(i).GetSide2())) {
			return i + 1;
		}
	}
	return -1;
}



bool Player::StartMexicanTrain(Train* trainslist[], int  & tilenumber, Train & train)
{
	if ((**(trainslist + 2)).Size() == 1 && CanPlayinTrain(**(trainslist + 2))) {
	
		tilenumber = GetPlayableTile(**(trainslist + 2));
		train = **(trainslist+2) ;
		return true;
			
	}
	else {
		return false;
	}
	
}

void Player::MoveTiletoTrain(Train * trainslist[], int tilenumber, Train train)
{	
	Tile tiletoadd = GetPlayerTiles().at(tilenumber - 1);
	//here train type is checked because we cannot modify on the copy of the train object.
	if (train.trainType() == "usertrain") {
		CheckTrainMove(**trainslist ,tiletoadd, tilenumber);

	}
	else if (train.trainType() == "computertrain") {
		CheckTrainMove(**(trainslist + 1), tiletoadd, tilenumber);

	}
	else if (train.trainType() == "mexicantrain") {
		CheckTrainMove(**(trainslist + 2), tiletoadd, tilenumber);
	}
	else {
		cout << "train type is: " << train.trainType() << endl;
	}
	
	

}

bool Player::Playopponenttrain( Train * trainslist[], Train opponentTrain, int & tilenumber, Train &  train )
{

	//opponent train is just a copy and not reference as it is used for searching a double tile and not modyfying it.
	if (opponentTrain.isTrainMarked()) {
		if (CanPlayDouble(opponentTrain)) {
			tilenumber = GetPlayableDouble(opponentTrain);
			train = opponentTrain;
			return true;

		}
		else if (CanPlayinTrain(opponentTrain)) {
			tilenumber = GetPlayableTile(opponentTrain);
			train = opponentTrain;
			return true;

		}


	}
	return false;
}


bool Player::PlayOrphanDoublemove(Train* trainslist[], int & tilenumber, Train& train, Train & opponentTrain)
{
	bool opponentplayable = opponentTrain.isTrainMarked();
	string opponenttrain = opponentTrain.trainType();
	if (opponentplayable) {
		//should be able to play double on the user train and non double on any other train.
		if (CanPlayDouble(**trainslist)) {
			if (CanPlayNonDouble(**(trainslist + 1)) || CanPlayNonDouble(**(trainslist + 2))) {
				tilenumber= GetPlayableDouble(**trainslist);
				train=**trainslist;
				return true;
			}
		}
		else if (CanPlayDouble(**(trainslist+1))) {
			if (CanPlayNonDouble(**(trainslist)) || CanPlayNonDouble(**(trainslist + 2))) {
				tilenumber = GetPlayableDouble(**(trainslist+1));
				train = **(trainslist+1);
				return true;
			}
		}
		else if (CanPlayDouble(**(trainslist+2))) {
			if (CanPlayNonDouble(**(trainslist)) || CanPlayNonDouble(**(trainslist + 1))) {
				tilenumber = GetPlayableDouble(**(trainslist + 2));
				train = **(trainslist + 2);
				return true;
			}
		}
		else {
			return false;
		}
	}
	else {
		if (opponentTrain.trainType() == "computertrain") {

			if (CanPlayDouble(**trainslist)  && CanPlayNonDouble(**(trainslist+2)) ) {
				tilenumber = GetPlayableDouble(**trainslist);
				train = **trainslist;
				return true;
			}
			else if (CanPlayDouble(**(trainslist+2))  && CanPlayNonDouble(**trainslist)) {
				tilenumber = GetPlayableDouble(**(trainslist+2));
				train = **(trainslist+2);
				return true;
			}

		}
		else if (opponentTrain.trainType()=="usertrain") {
			if (CanPlayDouble(**(trainslist+1)) && CanPlayNonDouble(**(trainslist + 2))) {
				tilenumber = GetPlayableDouble(**(trainslist+1));
				train = **(trainslist+1);
				return true;
			}
			else if (CanPlayDouble(**(trainslist + 2)) && CanPlayNonDouble(**(trainslist+1))) {
				tilenumber = GetPlayableDouble(**(trainslist + 2));
				train = **(trainslist + 2);
				return true;
			}
		}
		else {
			return false;
		}
	}
	return false;

}

bool Player::PlayMexicanTrain(Train* trainslist[], int& tilenumber, Train& train)
{
	if (CanPlayinTrain(**(trainslist + 2))) {
		tilenumber= GetPlayableTile(**(trainslist + 2));
		train = **(trainslist + 2);
		return true;
	}
	return false;
}

bool Player::PlaySelfTrain(Train* trainslist[], int& tilenumber, Train selftrain)
{
	if (CanPlayinTrain(selftrain)) {
		tilenumber = GetPlayableTile(selftrain);
		return true;
	}
	return false;
}


