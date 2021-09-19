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
     
    //pushing engine tile to the player train,computer train and mexican as they start from there.
    //playerTrain=  new Train("playertrain");
    //playerTrain->Addtile(engineTile);

    trainsList[0] = new Train("usertrain");
    trainsList[0]->Addtile(engineTile);
    //playerTrain = trainsList[0];

    //computerTrain=new Train("computertrain");
    //computerTrain->Addtile(engineTile);


    trainsList[1] = new Train("computertrain");
    cout <<"train type is:"<< trainsList[1]->trainType();
    trainsList[1]->Addtile(engineTile);
    //computerTrain = trainsList[1];


    //mexicanTrain = new Train("mexicantrain");
    //mexicanTrain->Addtile(engineTile);

    trainsList[2] = new Train("mexicantrain");
    trainsList[2]->Addtile(engineTile);
    //mexicanTrain = trainsList[2];

}

//displays the trains and tiles on the screen.
void Round::DisplayGame()
{
    
    //------------------------------------------------------------------------------Displays Players remaing tiles---------------------------------------------------------
    cout << " Player Tiles:" << endl;
    DisplayallTiles(playersList[1]->GetPlayerTiles());
    cout << endl;

//---------------------------------------displays the user player train-------------------------------------------------------------------------------------------
    
    int defaultspacing = 80;
    cout << setw(defaultspacing) << "Marker: " << trainsList[0]->marked() << endl;
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
    cout << setw(defaultspacing) << "Marker: " << trainsList[1]->marked() << endl;

   //---------------------------------------------------------------Displays  computer players remaining tiles-------------------------------------------------------------

   
    cout << endl;
    cout << " Computer Tiles:" << endl;
    DisplayallTiles(playersList[0]->GetPlayerTiles());

    //---------------------------------------------------------------Displays remaining boneyard tiles-------------------------------------------------------------------------
    
    
    cout << "------------------------------------------------------------------------------------------------------------"<< endl;
    cout << " Boneyard Tiles:" << endl;
    DisplayallTiles(boneyardTiles);

  
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

void Round::PlayMoves(bool playerfirst)
{
    
    //bug: when a opponent player plays on a marked train marked is removed
    // two double tiles can only be played if The player can play an additional third non-double tile from the player's hand
    //display a game tiles before the move is made by either a computer or an user.

    DisplayGame();
    //this helps to run the player first or computer first sequence
    if (playerfirst) {
        
        bool replay = false;
        int continousplay = 0;
       
        do
        {
            
            //this will help the user to replay a turn in case of the orphan double
            replay = playersList[1]->Mainmove(trainsList, boneyardTiles, continousplay);
            system("CLS");
            DisplayGame();
            continousplay++;
           
        } while (replay);
    }

   

    while (Playpossible())
    {
        
        
        bool replay = false;
        int continousplay = 0;

        do
        {   //this will help the user to replay a turn in case of the orphan double
            replay= playersList[0]->Mainmove(trainsList, boneyardTiles,continousplay);
            system("CLS");
            DisplayGame();
            continousplay++;
            
        }while (replay);

        //resetting the continous play to 0 as new user is playing
        continousplay = 0;
   
        if (Playpossible())
        {
            do
            {
                //this will help the user to replay a turn in case of the orphan double
                replay = playersList[1]->Mainmove(trainsList, boneyardTiles, continousplay);
                system("CLS");
                DisplayGame();
                continousplay++;
              
            } while (replay);
        
        }
        
        
    }
   

    //calculates the round score after the end of the game.
    for (auto& it : playersList[1]->GetPlayerTiles()) {
       
        playerscore = playerscore+  it.GetSide1() + it.GetSide2();
        
    }
    for (auto& it : playersList[0]->GetPlayerTiles()) {

        computerscore = computerscore+ it.GetSide1() + it.GetSide2();
        
    }
    
 
      
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


