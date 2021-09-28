/*
************************************************************
* Name:  Bishal Thapa									   *
* Project:  Project 1 Mexican Train C++				       *
* Class:  CMPS366 OPL				                       *
* Date:  09/27/2020				                           *
************************************************************
*/


#include "Round.h"
//Initializing the deck
void Round::Initializegame() {
    Deck mydeck = Deck();

    //Get the engine Tile based on the round of the game;
     engineTile = mydeck.GetEngineTile(currentRound);

    //Shuffling the deck after getting the engine tile.
    mydeck.ShuffleDeck();


    //Computer Player for the game
    playersList[0] = new Computer(mydeck.GetComputerTiles());

    //User player initialized with the random 16 tiles being assigned.
    playersList[1] = new User(mydeck.GetPlayerTiles());


    //Getting the boneyard tiles.
    boneyardTiles = mydeck.GetBoneyardTiles();
     
    //user train object
    trainsList[0] = new Train("usertrain");
    trainsList[0]->Addtile(engineTile);
   
    //computer train object
    trainsList[1] = new Train("computertrain");
    trainsList[1]->Addtile(engineTile);
  
    //mexican train object.
    trainsList[2] = new Train("mexicantrain");
    trainsList[2]->Addtile(engineTile);

}
void Round::InitializefromFile(vector<Tile> userTrain, vector<Tile> computerTrain,
    vector<Tile> mexicanTrain, bool a_usertrainmarked, bool a_computertrainmarked, vector<Tile> boneyard, vector<Tile> userTiles, vector <Tile> computerTiles) {
    
  
    //Get the engine Tile as the first element of the user train.
    engineTile = userTrain.at(0);
    
    //Computer Player for the game
    playersList[0] = new Computer(computerTiles);

    //User player initialized with the random 16 tiles being assigned.
    playersList[1] = new User(userTiles);


    //Getting the boneyard tiles.
    boneyardTiles = boneyard;

    //user train object
    trainsList[0] = new Train("usertrain");
    for (int i = 0; i < userTrain.size(); i++) {
        trainsList[0]->Addtile(userTrain[i]);
    }

    //computer train object
    trainsList[1] = new Train("computertrain");
    for (int i =computerTrain.size()-1 ; i >=0; i--) {
        trainsList[1]->Addtile(computerTrain[i]);
    }

    //mexican train object.
    trainsList[2] = new Train("mexicantrain");

    //as mexican train doesnot have engine tile added.
    trainsList[2]->Addtile(engineTile);
    for (int i = 0; i < mexicanTrain.size(); i++) {
        trainsList[2]->Addtile(mexicanTrain[i]);
    }

    if (a_usertrainmarked) {
        trainsList[0]->MarkTrain();
    }
    if (a_computertrainmarked) {
        trainsList[1]->MarkTrain();
    }
}

//displays the trains and tiles on the screen.
void Round::DisplayGame()
{

    cout << "Current Round is : " << currentRound << endl;
    cout << "Human score before this round: " << totalplayer << "  Computer score before this round: " << totalcomputer << endl;
    cout << "____________________________________________________________________________________________" << endl;
//------------------------------------------------------------------------------Displays Players remaing tiles---------------------------------------------------------
    cout << " Human Player Tiles:" << endl;
    DisplayallTiles(playersList[1]->GetPlayerTiles());
    cout << endl;

//---------------------------------------displays the user player train-------------------------------------------------------------------------------------------
    
    int defaultspacing = 80;
    cout << setw(defaultspacing) <<"user train-->" << endl;
    //FIRST LINE
    DisplayPlayerDouble(defaultspacing);

    //SECOND LINE
    DisplayPlayerMiddleTile(defaultspacing);

    //THIRD LINE
    DisplayPlayerDouble(defaultspacing);

//---------------------------------------displays the mexican train-------------------------------------------------------------------------------------------
    //first line
    DisplayMexicanDouble(defaultspacing);
    
    //second line
    
    DisplayMexicanMiddleTile(defaultspacing);
 
    //third line
    //this line displays A ENGINE tile
    DisplayMexicanDouble(defaultspacing);

    //---------------------------------------displays the computer player train-------------------------------------------------------------------------------------------
    
    int computerspacing = 86 - trainsList[1]->Size() * 5;
    //this function displays the first line of the computer tiles and helps for displaying double tiles effectively  
    DisplayComputerdouble(computerspacing);

    //second line for computer train
    DisplayComputerMiddleTile(computerspacing);

    //third line for computer train
    DisplayComputerdouble(computerspacing);
    cout << setw(defaultspacing) << "<- computer train " << endl;

   //---------------------------------------------------------------Displays  computer players remaining tiles-------------------------------------------------------------

   
    cout << endl;
    cout << " Computer Tiles:" << endl;
    DisplayallTiles(playersList[0]->GetPlayerTiles());

    //---------------------------------------------------------------Displays remaining boneyard tiles-------------------------------------------------------------------------
    
    
    cout << "------------------------------------------------------------------------------------------------------------"<< endl;
    cout << " Next Boneyard Tile:->" ;
    //yDisplayalltiles if needed to display all boneyard tiles
    //DisplayallTiles(boneyardTiles);
    if (boneyardTiles.size() == 0) { cout << "Empty"; }
    else {
        cout << boneyardTiles.at(0).GetSide1() << "-" << boneyardTiles.at(0).GetSide2() << endl;
    }
    cout << "--------------------------------------------------------------------------------------------------------" << endl;
  
}

void Round::DisplayComputerdouble(int spacing) {
    //first line for computer train
    cout << setw(spacing);
    for (int i = trainsList[1]->Size() - 1; i > 0; i--) {

        Tile currenttile = trainsList[1]->GetAllTiles().at(i);

        if (currenttile.GetSide1() == currenttile.GetSide2()) {
            cout << "--" << currenttile.GetSide1() << "--";
        }
        else {
            cout << "-" << "---" << "-";
        }
    }
    cout << endl;
}

void Round::DisplayComputerMiddleTile(int spacing) {
    cout << setw(spacing);
    if (trainsList[1]->isTrainMarked()) { cout << "(M)"; }
    for (int i = trainsList[1]->Size() - 1; i > 0; i--) {
        Tile currenttile = trainsList[1]->GetAllTiles().at(i);
        if (currenttile.GetSide1() == currenttile.GetSide2()) {
            cout << "|" << "-" << "|" << "-" << "|";
        }
        else {
            cout << "|" << currenttile.GetSide2() << "-" << currenttile.GetSide1() << "|";
        }
    }
    cout << endl;
}

void Round::DisplayPlayerDouble(int spacing){
    cout << setw(spacing);

    for (int i = 1; i < trainsList[0]->Size(); i++) {

        Tile currenttile = trainsList[0]->GetAllTiles().at(i);

        if (currenttile.GetSide1() == currenttile.GetSide2()) {
            cout << "--" << currenttile.GetSide1() << "--";
        }
        else {
            cout << "-" << "---" << "-";
        }


    }
    cout << endl;
}

void Round::DisplayallTiles(vector<Tile> tiles)
{
    int counter = 0;

    for (auto& it :tiles) {
        counter++;
        // Print the values
        cout << " | " << "  (" << counter << ")-> " << it.GetSide1() << "-" << it.GetSide2() << " | ";
        if (counter % 6 == 0) {
            cout << endl;

        }
    }
    cout << endl;
}

void Round::SerializeandQuit(int userscore, int computerscore, string nextplayer)
{
    string filename;
    //this prevents against empty filename and at least 2 chars expected
    while (filename.length() < 6) {
        filename = "";
        cout << "Enter the file name you want to save into (without .txt)" << endl;
        cin >> filename;
        filename = filename + ".txt";
    }
   
    
    ofstream MyFile(filename);

    // Write to the file
    MyFile << "Round: " <<currentRound;
    //for the computer
    MyFile << "\n\n";
    MyFile << "Computer:\n";
    MyFile << "   Score: " << computerscore << endl;
    MyFile << "   Hand: ";
    for (int i = 0; i < playersList[0]->GetPlayerTiles().size();i++) {
        MyFile << to_string(playersList[0]->GetPlayerTiles().at(i).GetSide1()) << "-" << to_string(playersList[0]->GetPlayerTiles().at(i).GetSide2()) << " ";
    }
    MyFile << "\n";
    MyFile << "   Train: ";
    if (trainsList[1]->isTrainMarked()) MyFile << "M ";
    for (int i = trainsList[1]->GetAllTiles().size() - 1; i >= 0; i--) {
        MyFile << to_string(trainsList[1]->GetAllTiles().at(i).GetSide2()) << "-" << to_string(trainsList[1]->GetAllTiles().at(i).GetSide1()) << " ";
    }
    //for the user 
    MyFile << "\n";
    MyFile << "Human:\n";
    MyFile << "   Score: " << userscore << endl;
    MyFile << "   Hand: ";
    for (int i = 0; i < playersList[1]->GetPlayerTiles().size(); i++) {
        MyFile << to_string(playersList[1]->GetPlayerTiles().at(i).GetSide1()) << "-" << to_string(playersList[1]->GetPlayerTiles().at(i).GetSide2()) << " ";
    }
    MyFile << "\n";
    MyFile << "   Train: ";
    for (int i = 0; i< trainsList[0]->GetAllTiles().size() ; i ++) {
        MyFile << to_string(trainsList[0]->GetAllTiles().at(i).GetSide1()) << "-" << to_string(trainsList[0]->GetAllTiles().at(i).GetSide2()) << " ";
    }
    if (trainsList[0]->isTrainMarked()) MyFile << "M";
    MyFile << "\n\n";
    MyFile << "Mexican Train: ";
    for (int i = 1; i < trainsList[2]->GetAllTiles().size(); i++) {
        MyFile << to_string(trainsList[2]->GetAllTiles().at(i).GetSide1()) << "-" << to_string(trainsList[2]->GetAllTiles().at(i).GetSide2()) << " ";
    }
    MyFile << "\n\n";
    MyFile << "Boneyard: ";
    for (int i = 0; i <boneyardTiles.size(); i++) {
        MyFile << to_string(boneyardTiles.at(i).GetSide1()) << "-" << to_string(boneyardTiles.at(i).GetSide2()) << " ";
    }
    MyFile << "\n\n";
    MyFile << "Next Player: " << nextplayer;

    // Close the file
    MyFile.close();
    cout << "Your file has been serialized" << endl;
    cout<<"-----------------------------------------------------------------------" << endl;

    return;
}

void Round::DisplayPlayerMiddleTile(int spacing) {
    cout << setw(spacing);


    for (int i = 1; i < trainsList[0]->Size(); i++) {

        Tile currenttile = trainsList[0]->GetAllTiles().at(i);
        if (currenttile.GetSide1() == currenttile.GetSide2()) {
            cout << "|" << "-" << "|" << "-" << "|";
        }
        else {
            cout << "|" << currenttile.GetSide1() << "-" << currenttile.GetSide2() << "|";
        }

    }
    if (trainsList[0]->isTrainMarked()) { cout << "(M)"; }
    cout << endl;
};

void Round::DisplayMexicanDouble(int spacing) {
    
    
    cout << setw(spacing) << engineTile.GetSide1();

    for (int i = 1; i < trainsList[2]->Size(); i++) {

        Tile currenttile = trainsList[2]->GetAllTiles().at(i);

        if (currenttile.GetSide1() == currenttile.GetSide2()) {
            cout << "--" << currenttile.GetSide1() << "--";
        }
        else {
            cout << "-" << "---" << "-";
        }


    }
    cout << endl;
}

void Round::DisplayMexicanMiddleTile(int spacing) {
    cout << setw(spacing) << "mexican train --> |";

    for (int i = 1; i < trainsList[2]->Size(); i++) {

        Tile currenttile = trainsList[2]->GetAllTiles().at(i);
        if (currenttile.GetSide1() == currenttile.GetSide2()) {
            cout << "|" << "-" << "|" << "-" << "|";
        }
        else {
            cout << "|" << currenttile.GetSide1() << "-" << currenttile.GetSide2() << "|";
        }

    }
    cout << endl;
};

bool Round::PlayMoves(bool playerfirst, int round, int a_totaluserscore, int a_totalcomputerscore)
{
    
    
    totalcomputer = a_totalcomputerscore;
    totalplayer = a_totaluserscore;
    bool quit = false;
    DisplayGame();
    //this helps to run the player first or computer first sequence
    if (playerfirst) {
        
        bool replay = false;
        int continousplay = 0;
       
        do
        { 
            //this will help the user to replay a turn in case of the orphan double
            replay = playersList[1]->PlayMove(trainsList, boneyardTiles, continousplay,quit);
            system("CLS");
            DisplayGame();
            continousplay++;
            if (quit) {
                SerializeandQuit(a_totaluserscore, a_totalcomputerscore, "Human");
                return false;
            }
           
        } while (replay);
    }

   

    while (Playpossible())
    {
        
        
        bool replay = false;
        int continousplay = 0;

        do
        {   //this will help the user to replay a turn in case of the orphan double
            replay= playersList[0]->PlayMove(trainsList, boneyardTiles,continousplay,quit);
            system("CLS");
            DisplayGame();
            continousplay++;
            if (quit)
            {
                SerializeandQuit(a_totaluserscore, a_totalcomputerscore, "Computer");
                return false;
            }
            
        }while (replay);

        //resetting the continous play to 0 as new user is playing
        continousplay = 0;
   
        if (Playpossible())
        {
            do
            {
                //this will help the user to replay a turn in case of the orphan double
                replay = playersList[1]->PlayMove(trainsList, boneyardTiles, continousplay,quit);
                system("CLS");
                DisplayGame();
                continousplay++;
                if (quit) {
                    SerializeandQuit(a_totaluserscore, a_totalcomputerscore, "Human");
                    return false;
                }
              
            } while (replay);
        
        }
        
        
    }
   

    //calculates the round score after the end of the game.
    for (auto& it : playersList[1]->GetPlayerTiles()) {
       
        playerscore = playerscore+  it.GetSide1() + it.GetSide2();
        
        
    }
    cout << "Human Player's score for the round:" << playerscore << endl;
    for (auto& it : playersList[0]->GetPlayerTiles()) {

        computerscore = computerscore + it.GetSide1() + it.GetSide2();
      
        
    }
    cout << "Computer Player's score for the round:" << computerscore << endl;
    
    return true;
      
}

bool Round::Playpossible()
{
    // if both user trains are marked and boneyard is empty.
    if (boneyardTiles.size() == 0 && trainsList[0]->isTrainMarked() && trainsList[1]->isTrainMarked()) {
        return false;
    }
    //if one of the player has emptied his hands.
    else if ((playersList[0]->GetPlayerTiles().size() == 0) || (playersList[1]->GetPlayerTiles().size() == 0))
    {
        return false;
    }
    else {
        return true;
    }
}


