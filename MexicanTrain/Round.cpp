#include "Round.h"
//Initializing the deck
void Round::Initializegame() {
    Deck mydeck = Deck();

    //Get the engine Tile based on the round of the game;
     engineTile = mydeck.GetEngineTile(currentRound);

    //Shuffling the deck after getting the engine tile.
    mydeck.ShuffleDeck();

   
     
     //Computer Player for the game
     computerplayer = new Computer(mydeck.GetComputerTiles());

     //User player initialized with the random 16 tiles being assigned.
     userplayer = new User(mydeck.GetPlayerTiles());

     
     
     
     //Getting the boneyard tiles.
     boneyardTiles = mydeck.GetBoneyardTiles();
     
     //pushing engine tile to the player train,computer train and mexican as they start from there.
     playerTrain=  new Train("playertrain");
     playerTrain->Addtiles(engineTile);

     computerTrain=new Train("computertrain");
     computerTrain->Addtiles(engineTile);

     mexicanTrain = new Train("mexicantrain");
     mexicanTrain->Addtiles(engineTile);
    


}

//displays the trains and tiles on the screen.
void Round::DisplayGame()
{
    cout << " Player Tiles:" << endl;
    int counter = 0;
    
    for (auto& it : userplayer->GetPlayerTiles()) {
        counter++;
        // Print the values
        cout << " | " << "  (" << counter << ")-> " << it.GetSide1() << "-" << it.GetSide2() << " | ";
        if (counter% 6==0) {
            cout << endl;
           
        }
    }



    cout << endl << endl << endl;
    cout << "                                        Player train" << endl;
    for (auto& it : playerTrain->ReturnAllTiles()) {
        counter++;
        // Print the values
        cout << " | "  << it.GetSide1() << "-" << it.GetSide2() << " | ";
        
    }
    cout << endl;
    cout << "                                        engine tile" << endl;
    cout << "                                           " << engineTile.GetSide1()<< endl;
    cout << "                                           " << "|" << endl;
    cout << "                                           " << engineTile.GetSide2() << endl;
    
    cout << "                                        Computer train" << endl;
    for (auto& it : computerTrain->ReturnAllTiles()) {
        counter++;
        // Print the values
        cout << " | "  << it.GetSide1() << "-" << it.GetSide2() << " | ";

    }
    cout << endl;
    cout << endl << endl << endl;
    cout << " Computer Tiles:" << endl;
    counter = 0;
    for (auto& it : computerplayer->GetPlayerTiles()) {
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

void Round::PlayMoves()
{
    
    //this should call for player as well as computer moves.

    /*unsigned int tilenumber = 0;
    //if the tile chosen can be attached with train chosen.
    bool validtile = false;
    //validating the tilenumber so that user chooses a valid tilenumber to play
    while(!validtile)
    {
        cout << "please enter the tile(1-16) you want to pick" << endl;
        cin >> tilenumber;
        
        if (tilenumber >= 1 && tilenumber <= playerTiles.size()) 
        {
            char train = 'X';
            //validating the user chosen train
            //User chosen tile to be attached at the end of the train
            Tile nextmove = playerTiles.at(tilenumber - 1);

            while (!(train == 'U' || train == 'C' || train == 'M'))
            {
                cout << "please enter the Train(U-user,C-computer,M-mexican) you want to pick" << endl;
                cin >> train;
                //more validation to be done here.
                if (train == 'U')
                {
                    
                    //moving a user chosen tile to a Player train
                    if (nextmove.GetSide1() == playerTrain.back().GetSide1() || nextmove.GetSide2() == playerTrain.back().GetSide1())
                    {
                        playerTrain.push_back(nextmove);
                        playerTiles.erase(playerTiles.begin() + tilenumber - 1);
                        validtile = true;
                    }
                    else
                    {
                        cout << "The tile you chose cannot be placed on the user train" << endl;
                        
                    }
                }
                else if (train == 'C')
                {
                    if(computertrainmarked)
                    {
                        //moving a user chosen tile to a Computer train
                        if (nextmove.GetSide1() == computerTrain.back().GetSide1() || nextmove.GetSide2() == computerTrain.back().GetSide1())
                        {
                            computerTrain.push_back(nextmove);
                            playerTiles.erase(playerTiles.begin() + tilenumber - 1);
                            validtile = true;
                        }
                        else
                        {
                            cout << "The tile you chose cannot be placed on the computer's train" << endl;

                        }
                    
                    }
                    else {
                        cout << "You cannot add tiles to unmarked computer's train" << endl;
                    }
                    
                }
                else if (train == 'M')
                {
                    //moving a user chosen tile to a Computer train
                    if (nextmove.GetSide1() == MexicanTrain.back().GetSide1() || nextmove.GetSide2() == MexicanTrain.back().GetSide1())
                    {
                        MexicanTrain.push_back(nextmove);
                        playerTiles.erase(playerTiles.begin() + tilenumber - 1);
                        validtile = true;
                    }
                    else
                    {
                        cout << "The tile you chose cannot be placed on the Mexican train" << endl;

                    }
                }

            }
        }
        else
        {
            cout << "Enter a valid tile" << endl;
        }
        
        
    }
    */
      
}

void Round::MakeComputerMoves()
{
    cout << "computer should choose the best move!" << endl;
    system("CLS");
}
