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
     playerTrain=  new Train("playertrain");
     playerTrain->Addtile(engineTile);

     computerTrain=new Train("computertrain");
     computerTrain->Addtile(engineTile);

     mexicanTrain = new Train("mexicantrain");
     mexicanTrain->Addtile(engineTile);
    


}

//displays the trains and tiles on the screen.
void Round::DisplayGame()
{
    cout << " Player Tiles:" << endl;
    int counter = 0;
    
    for (auto& it : playersList[1]->GetPlayerTiles()) {
        counter++;
        // Print the values
        cout << " | " << "  (" << counter << ")-> " << it.GetSide1() << "-" << it.GetSide2() << " | ";
        if (counter% 6==0) {
            cout << endl;
           
        }
    }



    cout << endl << endl << endl;
    cout << "                                        Player train" << endl;
    for (auto& it : playerTrain->GetAllTiles()) {
        counter++;
        // Print the values
        cout << " | "  << it.GetSide1() << "-" << it.GetSide2() << " | ";
        
    }
    cout << endl;
    cout << "                                        engine tile" << endl;
    cout << "                                           " << engineTile.GetSide1()<< endl;
    cout << "                                           " << "|" ;

    for (auto& it : mexicanTrain->GetAllTiles()) {
        counter++;
        // Print the values
        cout << " | " << it.GetSide1() << "-" << it.GetSide2() << " | ";

    }
    cout << endl;
    cout << "                                           " << engineTile.GetSide2() << endl;
    
    cout << "                                        Computer train" << endl;
    for (auto& it : computerTrain->GetAllTiles()) {
        counter++;
        // Print the values
        cout << " | "  << it.GetSide1() << "-" << it.GetSide2() << " | ";

    }
    cout << endl;
    cout << endl << endl << endl;
    cout << " Computer Tiles:" << endl;
    counter = 0;
    for (auto& it : playersList[0]->GetPlayerTiles()) {
        counter++;
        // Print the values
        cout << " | "  << "  (" << counter << ")-> " << it.GetSide1() << "-" << it.GetSide2() <<" | " ;
        if (counter % 6==0) {
            cout << endl;
            
        }
    }
    counter = 0;
    cout << endl << endl << endl;
    cout << " Boneyard Tiles:" << endl;
    for (auto& it : boneyardTiles) {
        counter++;
        // Print the values
        cout << it.GetSide1() << "-" << it.GetSide2()<< "   " ;
        if (counter %6 ==0) {
            cout << endl;
           
        }
    }
    cout << endl;
}

void Round::PlayMoves(bool playerfirst)
{
    //this helps to run the player first or computer first sequence
   // if (playerfirst) {
     //   playersList[1]->Mainmove(*playerTrain, *computerTrain, *mexicanTrain, boneyardTiles);
      // system("CLS");
    //}/
    ///

    //game continues until boneyard tile, usertiles of

    //displaying a game before a user makes a move initially
    DisplayGame();
    while ( (boneyardTiles.size()!=0) && (playersList[0]->GetPlayerTiles().size()!=0) && (playersList[0]->GetPlayerTiles().size() != 0))
    {
        
       
        bool replay = false;
        //this one is computer
        int continousplay = 0;

        do
        {   //this will help the user to replay a turn in case of the orphan double
            replay= playersList[0]->Mainmove(*playerTrain, *computerTrain, *mexicanTrain, boneyardTiles,continousplay);
            system("CLS");
            DisplayGame();
            continousplay++;
            cout << " computer runs" << endl;
        }while (replay);

        //resetting the continous play to 0 as new user is playing
        continousplay = 0;
   
        do
        {
            //this will help the user to replay a turn in case of the orphan double
            replay = playersList[1]->Mainmove(*playerTrain, *computerTrain, *mexicanTrain, boneyardTiles, continousplay);
            system("CLS");
            DisplayGame();
            continousplay++;
            cout << " user runs" << endl;
        } while (replay);

        
    }
   

    //returns the round score here.
    

    
 
      
}


