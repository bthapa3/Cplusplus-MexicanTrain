/*
************************************************************
* Name:  Bishal Thapa									   *
* Project:  Project 1 Mexican Train C++				       *
* Class:  CMPS366 OPL				                       *
* Date:  09/27/2020				                           *
************************************************************
*/


#include "Round.h"


/* *********************************************************************
Function Name:	Initializegame()

Purpose:		
                Create a new deck and use the deck ton initialize a new round and store the tiles from deck
                to the player tiles, computer tiles, boneyard.
Parameters:
                none

Return Value:
                none.
Algorithm:
                none.

Assistance Received: none
********************************************************************* */
void Round::Initializegame() {
    Deck mydeck = Deck();

    //Get the engine Tile based on the round of the game;
     m_engineTile = mydeck.GetEngineTile(m_currentRound);

    //Shuffling the deck after getting the engine tile.
    mydeck.ShuffleDeck();


    //Computer Player for the game
    m_playersList[0] = new Computer(mydeck.GetComputerTiles());

    //User player initialized with the random 16 tiles being assigned.
    m_playersList[1] = new User(mydeck.GetPlayerTiles());


    //Getting the boneyard tiles.
    m_boneyardTiles = mydeck.GetBoneyardTiles();
     
    //user train object
    m_trainsList[0] = new Train("usertrain");
    m_trainsList[0]->Addtile(m_engineTile);
   
    //computer train object
    m_trainsList[1] = new Train("computertrain");
    m_trainsList[1]->Addtile(m_engineTile);
  
    //mexican train object.
    m_trainsList[2] = new Train("mexicantrain");
    m_trainsList[2]->Addtile(m_engineTile);

}


/* *********************************************************************
Function Name:	InitializefromFile()

Purpose:
              Initialize a game from file without creating a deck. All the tiles and variables required for 
              initializing the game are passed as parameters.

Parameters:
                1) a_userTrain --> vector of tiles of the user train
                2) a_computerTrain --> vector of tiles for the computer train.
                3) a_mexicanTrain --> vector of tiles for the mexican train.
                4) a_usertrainmarked --> boolean value that states if the user train is marked or not.
                5) a_computertrainmarked --> boolean value that states if the computer train is marked or not.
                6) a_boneyard --> vector of tiles for the boneyard
                7) a_userTiles --> vector of tiles of the list of player tiles
                8) a_computerTiles --> vector of tiles of the list of computer tiles.

Return Value:
                none.
Algorithm:
                none.

Assistance Received: none
********************************************************************* */
void Round::InitializefromFile(vector<Tile> a_userTrain, vector<Tile> a_computerTrain,
    vector<Tile> a_mexicanTrain, bool a_usertrainmarked, bool a_computertrainmarked, vector<Tile> a_boneyard, vector<Tile> a_userTiles, vector <Tile> a_computerTiles) {
    
  
    //Get the engine Tile as the first element of the user train.
    m_engineTile = a_userTrain.at(0);
    
    //Computer Player for the game
    m_playersList[0] = new Computer(a_computerTiles);

    //User player initialized with the random 16 tiles being assigned.
    m_playersList[1] = new User(a_userTiles);


    //Getting the boneyard tiles.
    m_boneyardTiles = a_boneyard;

    //user train object
    m_trainsList[0] = new Train("usertrain");
    for (int i = 0; i < a_userTrain.size(); i++) {
        m_trainsList[0]->Addtile(a_userTrain[i]);
    }

    //computer train object
    m_trainsList[1] = new Train("computertrain");
    for (int i =a_computerTrain.size()-1 ; i >=0; i--) {
        m_trainsList[1]->Addtile(a_computerTrain[i]);
    }

    //mexican train object.
    m_trainsList[2] = new Train("mexicantrain");

    //as mexican train doesnot have engine tile added.
    m_trainsList[2]->Addtile(m_engineTile);
    for (int i = 0; i < a_mexicanTrain.size(); i++) {
        m_trainsList[2]->Addtile(a_mexicanTrain[i]);
    }

    if (a_usertrainmarked) {
        m_trainsList[0]->MarkTrain();
    }
    if (a_computertrainmarked) {
        m_trainsList[1]->MarkTrain();
    }
}


/* *********************************************************************
Function Name:	    DisplayGame()   

Purpose:
                Helps to display user tiles, computer tiles, boneyard tiles and all the trains.
                This function is refreshed after each move to show the updates to the user.

Parameters:

Return Value:
                none.
Algorithm:
                none.

Assistance Received: none
********************************************************************* */
void Round::DisplayGame()
{

    cout << "Current Round is : " << m_currentRound << endl;
    cout << "Human score before this round: " << m_totalplayer << "  Computer score before this round: " << m_totalcomputer << endl;
    cout << "____________________________________________________________________________________________" << endl;
//------------------------------------------------------------------------------Displays Players remaing tiles---------------------------------------------------------
    cout << " Human Player Tiles:" << endl;
    DisplayallTiles(m_playersList[1]->GetPlayerTiles());
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
    
    int computerspacing = 86 - m_trainsList[1]->Size() * 5;
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
    DisplayallTiles(m_playersList[0]->GetPlayerTiles());

    //---------------------------------------------------------------Displays remaining boneyard tiles-------------------------------------------------------------------------
    
    
    cout << "------------------------------------------------------------------------------------------------------------"<< endl;
    cout << " Next Boneyard Tile:->" ;
    //yDisplayalltiles if needed to display all boneyard tiles
    //DisplayallTiles(boneyardTiles);
    if (m_boneyardTiles.size() == 0) { cout << "Empty"; }
    else {
        cout << m_boneyardTiles.at(0).GetSide1() << "-" << m_boneyardTiles.at(0).GetSide2() << endl;
    }
    cout << "--------------------------------------------------------------------------------------------------------" << endl;
  
}

/* *********************************************************************
Function Name:	    DisplayComputerdouble

Purpose:
                    Helps to set a tile vertical in case of the double tile. This is for line
                    1 and 3 of the 3 lines.

Parameters:
                1) int a_spacing --> number of spaces used for the purpose of 
                displaying a computer tile on the left side of engine tile.

Return Value:
                none.
Algorithm:
                if tile is double, display tile number on line 1 and 3. Else display  '---'

Assistance Received: none
********************************************************************* */
void Round::DisplayComputerdouble(int a_spacing) {
    //first line for computer train
    cout << setw(a_spacing);
    for (int i = m_trainsList[1]->Size() - 1; i > 0; i--) {

        Tile currenttile = m_trainsList[1]->GetAllTiles().at(i);

        if (currenttile.GetSide1() == currenttile.GetSide2()) {
            cout << "--" << currenttile.GetSide1() << "--";
        }
        else {
            cout << "-" << "---" << "-";
        }
    }
    cout << endl;
}


/* *********************************************************************
Function Name:	    DisplayComputerMiddleTile

Purpose:
                    Helps to set a tile vertical in case of the double tile. This is for line
                    2 of the 3 lines.

Parameters:
                1) int a_spacing --> number of spaces used for the purpose of
                displaying a computer tile on the left side of engine tile.

Return Value:
                none.
Algorithm:
                if tile is double, display '|-|' on the line 2. Else display tile horizontally.
                Display "M" in case computer train is marked.
Assistance Received: none
********************************************************************* */
void Round::DisplayComputerMiddleTile(int a_spacing) {
    cout << setw(a_spacing);
    if (m_trainsList[1]->isTrainMarked()) { cout << "(M)"; }
    for (int i = m_trainsList[1]->Size() - 1; i > 0; i--) {
        Tile currenttile = m_trainsList[1]->GetAllTiles().at(i);
        if (currenttile.GetSide1() == currenttile.GetSide2()) {
            cout << "|" << "-" << "|" << "-" << "|";
        }
        else {
            cout << "|" << currenttile.GetSide2() << "-" << currenttile.GetSide1() << "|";
        }
    }
    cout << endl;
}


/* *********************************************************************
Function Name:	    DisplayPlayerdouble

Purpose:
                    Helps to set a tile vertical in case of the double tile. This is for line
                    1 and 3 of the 3 lines.

Parameters:
                1) int a_spacing --> number of spaces used for the purpose of
                displaying a computer tile on the right side.

Return Value:
                none.
Algorithm:
                if tile is double, display tile number on line 1 and 3. Else display  '---'

Assistance Received: none
********************************************************************* */
void Round::DisplayPlayerDouble(int a_spacing){
    cout << setw(a_spacing);

    for (int i = 1; i < m_trainsList[0]->Size(); i++) {

        Tile currenttile = m_trainsList[0]->GetAllTiles().at(i);

        if (currenttile.GetSide1() == currenttile.GetSide2()) {
            cout << "--" << currenttile.GetSide1() << "--";
        }
        else {
            cout << "-" << "---" << "-";
        }


    }
    cout << endl;
}

/* *********************************************************************
Function Name:	    DisplayallTiles

Purpose:            Helps to display all the tiles present in the vector.

Parameters:
                1) int a_tiles --> vector that contains tiles .

Return Value:
                none.
Algorithm:
                iterate through the vector to display all the tiles. After 6 tiles break a line so 
                that tiles donot look clustered.

Assistance Received: none
********************************************************************* */
void Round::DisplayallTiles(vector<Tile> a_tiles)
{
    int counter = 0;

    for (auto& it :a_tiles) {
        counter++;
        // Print the values
        cout << " | " << "  (" << counter << ")-> " << it.GetSide1() << "-" << it.GetSide2() << " | ";
        if (counter % 6 == 0) {
            cout << endl;

        }
    }
    cout << endl;
}

/* *********************************************************************
Function Name:	    DisplayPlayerMiddleTile

Purpose:
                    Helps to set a tile vertical in case of the double tile. This is for line
                    2 of the 3 lines.

Parameters:
                1) int a_spacing --> number of spaces used for the purpose of
                displaying a human player train on the right side of engine tile.

Return Value:
                none.
Algorithm:
                if tile is double, display '|-|' on the line 2. Else display tile horizontally.
                Also display 'M' in case of human train is marked

Assistance Received: none
********************************************************************* */
void Round::DisplayPlayerMiddleTile(int a_spacing) {
    cout << setw(a_spacing);


    for (int i = 1; i < m_trainsList[0]->Size(); i++) {

        Tile currenttile = m_trainsList[0]->GetAllTiles().at(i);
        if (currenttile.GetSide1() == currenttile.GetSide2()) {
            cout << "|" << "-" << "|" << "-" << "|";
        }
        else {
            cout << "|" << currenttile.GetSide1() << "-" << currenttile.GetSide2() << "|";
        }

    }
    if (m_trainsList[0]->isTrainMarked()) { cout << "(M)"; }
    cout << endl;
};



/* *********************************************************************
Function Name:	    DisplayMexicandouble

Purpose:
                    Helps to set a tile vertical in case of the double tile. This is for line
                    1 and 3 of the 3 lines.

Parameters:
                1) int a_spacing --> number of spaces used for the purpose of
                displaying a mexican train on the right side.

Return Value:
                none.
Algorithm:
                if tile is double, display tile number on line 1 and 3. Else display  '---'

Assistance Received: none
********************************************************************* */
void Round::DisplayMexicanDouble(int a_spacing) {


    cout << setw(a_spacing) << m_engineTile.GetSide1();

    for (int i = 1; i < m_trainsList[2]->Size(); i++) {

        Tile currenttile = m_trainsList[2]->GetAllTiles().at(i);

        if (currenttile.GetSide1() == currenttile.GetSide2()) {
            cout << "--" << currenttile.GetSide1() << "--";
        }
        else {
            cout << "-" << "---" << "-";
        }


    }
    cout << endl;
}


/* *********************************************************************
Function Name:	    DisplayMexicanMiddleTile

Purpose:
                    Helps to set a tile vertical in case of the double tile. This is for line
                    2 of the 3 lines.

Parameters:
                1) int a_spacing --> number of spaces used for the purpose of
                displaying a mexican train on the right side of engine tile.

Return Value:
                none.
Algorithm:
                if tile is double, display '|-|' on the line 2. Else display tile horizontally.
                Also display 'M' in case of human train is marked

Assistance Received: none
********************************************************************* */
void Round::DisplayMexicanMiddleTile(int a_spacing) {
    cout << setw(a_spacing) << "mexican train --> |";

    for (int i = 1; i < m_trainsList[2]->Size(); i++) {

        Tile currenttile = m_trainsList[2]->GetAllTiles().at(i);
        if (currenttile.GetSide1() == currenttile.GetSide2()) {
            cout << "|" << "-" << "|" << "-" << "|";
        }
        else {
            cout << "|" << currenttile.GetSide1() << "-" << currenttile.GetSide2() << "|";
        }

    }
    cout << endl;
};
/* *********************************************************************
Function Name:	    SerializeandQuit

Purpose:            Helps to write the current state of the game to the text file.

Parameters:
                1) int a_userscore --> current score of the human player
                2) int a_computerscore --> current score of the computer player
                3) a_nextplayer --> next player on the line

Return Value:
                none.
Algorithm:
                none.

Assistance Received: none
********************************************************************* */



void Round::SerializeandQuit(int a_userscore, int a_computerscore, string a_nextplayer)
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
    MyFile << "Round: " << m_currentRound;
    //for the computer
    MyFile << "\n\n";
    MyFile << "Computer:\n";
    MyFile << "   Score: " << m_computerscore << endl;
    MyFile << "   Hand: ";
    for (int i = 0; i < m_playersList[0]->GetPlayerTiles().size();i++) {
        MyFile << to_string(m_playersList[0]->GetPlayerTiles().at(i).GetSide1()) << "-" << to_string(m_playersList[0]->GetPlayerTiles().at(i).GetSide2()) << " ";
    }
    MyFile << "\n";
    MyFile << "   Train: ";
    if (m_trainsList[1]->isTrainMarked()) MyFile << "M ";
    for (int i = m_trainsList[1]->GetAllTiles().size() - 1; i >= 0; i--) {
        MyFile << to_string(m_trainsList[1]->GetAllTiles().at(i).GetSide2()) << "-" << to_string(m_trainsList[1]->GetAllTiles().at(i).GetSide1()) << " ";
    }
    //for the user 
    MyFile << "\n";
    MyFile << "Human:\n";
    MyFile << "   Score: " << a_userscore << endl;
    MyFile << "   Hand: ";
    for (int i = 0; i < m_playersList[1]->GetPlayerTiles().size(); i++) {
        MyFile << to_string(m_playersList[1]->GetPlayerTiles().at(i).GetSide1()) << "-" << to_string(m_playersList[1]->GetPlayerTiles().at(i).GetSide2()) << " ";
    }
    MyFile << "\n";
    MyFile << "   Train: ";
    for (int i = 0; i< m_trainsList[0]->GetAllTiles().size() ; i ++) {
        MyFile << to_string(m_trainsList[0]->GetAllTiles().at(i).GetSide1()) << "-" << to_string(m_trainsList[0]->GetAllTiles().at(i).GetSide2()) << " ";
    }
    if (m_trainsList[0]->isTrainMarked()) MyFile << "M";
    MyFile << "\n\n";
    MyFile << "Mexican Train: ";
    for (int i = 1; i < m_trainsList[2]->GetAllTiles().size(); i++) {
        MyFile << to_string(m_trainsList[2]->GetAllTiles().at(i).GetSide1()) << "-" << to_string(m_trainsList[2]->GetAllTiles().at(i).GetSide2()) << " ";
    }
    MyFile << "\n\n";
    MyFile << "Boneyard: ";
    for (int i = 0; i <m_boneyardTiles.size(); i++) {
        MyFile << to_string(m_boneyardTiles.at(i).GetSide1()) << "-" << to_string(m_boneyardTiles.at(i).GetSide2()) << " ";
    }
    MyFile << "\n\n";
    MyFile << "Next Player: " << a_nextplayer;

    // Close the file
    MyFile.close();
    cout << "Your file has been serialized" << endl;
    cout<<"-----------------------------------------------------------------------" << endl;

    return;
}


/* *********************************************************************
Function Name:	    PlayMoves

Purpose:           Run the game until the game is over In order to do this this class display user moves,
                    takes input and make changes to player and train objects.

Parameters:
                1) int a_playerfirst -->boolean value that states if the human player goes first
                2) int a_ round --> integer value of the current round
                3) int a_totaluserscore --> total human player score before this round
                4) int a_totalcomputerscore --> total computer score before this round


Return Value:
               boolean - false if game need to be serialized and quit, true otherwise.
Algorithm:
                none.

Assistance Received: none
********************************************************************* */


bool Round::PlayMoves(bool a_playerfirst, int a_round, int a_totaluserscore, int a_totalcomputerscore)
{
    
    //updates the global total score.
    m_totalcomputer = a_totalcomputerscore;
    m_totalplayer = a_totaluserscore;
    bool quit = false;
    DisplayGame();
    //this helps to run the player first or computer first sequence
    if (a_playerfirst) {
        
        //decides if the user can play one more move or not
        bool replay = false;
        int continousplay = 0;
       
        do
        { 
            //this will help the user to replay a turn in case of the orphan double
            replay = m_playersList[1]->PlayMove(m_trainsList, m_boneyardTiles, continousplay,quit);
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
            replay= m_playersList[0]->PlayMove(m_trainsList, m_boneyardTiles,continousplay,quit);
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
                replay = m_playersList[1]->PlayMove(m_trainsList, m_boneyardTiles, continousplay,quit);
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
    for (auto& it : m_playersList[1]->GetPlayerTiles()) {
       
        m_playerscore = m_playerscore+  it.GetSide1() + it.GetSide2();
        
        
    }
    cout << "Human Player's score for the round:" << m_playerscore << endl;
    for (auto& it : m_playersList[0]->GetPlayerTiles()) {

        m_computerscore = m_computerscore + it.GetSide1() + it.GetSide2();
      
        
    }
    cout << "Computer Player's score for the round:" << m_computerscore << endl;
    
    
    //deleting the train and player objects pointer to prevent memory leak
    for (int i = 0; i < 3; i++) {
        m_trainsList[i]->~Train();
        delete m_trainsList[i];
    }
    for (int i = 0; i < 2; i++) {
        m_playersList[i]->~Player();
        delete m_playersList[i];
    }

    return true;
    
}


/* *********************************************************************
Function Name:	    Playpossible

Purpose:          This function checks if the game is over.

Parameters:
               none


Return Value:
               boolean - true if the game is over, false otherwise.
Algorithm:
               if one of the computer or human player has no tiles left game is over, else if both the 
               trains are marked and there is no boneyard tiles left game is over.

Assistance Received: none
********************************************************************* */
bool Round::Playpossible()
{
    // if both user trains are marked and boneyard is empty.
    if (m_boneyardTiles.size() == 0 && m_trainsList[0]->isTrainMarked() && m_trainsList[1]->isTrainMarked()) {
        return false;
    }
    //if one of the player has emptied his hands.
    else if ((m_playersList[0]->GetPlayerTiles().size() == 0) || (m_playersList[1]->GetPlayerTiles().size() == 0))
    {
        return false;
    }
    else {
        return true;
    }
}


