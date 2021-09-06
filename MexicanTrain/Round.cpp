#include "Round.h"
//Initializing the deck
void Round::Initializegame() {
    Deck mydeck = Deck();

    //Get the engine Tile based on the round of the game;
     engineTile = mydeck.GetEngineTile(currentRound);

    //Shuffling the deck after getting the engine tile.
    mydeck.ShuffleDeck();

    //Getting the player tiles.
     playerTiles = mydeck.GetPlayerTiles();
    //Getting the computer tiles.
     computerTiles = mydeck.GetComputerTiles();
    //Getting the boneyard tiles.
     boneyardTiles = mydeck.GetBoneyardTiles();

}

void Round::PlayGame()
{
    cout << " Player Tiles:" << endl;
    int counter = 0;
   
    for (auto& it : playerTiles) {
        counter++;
        // Print the values
        cout << " | " << "  (" << counter << ")-> " << it.GetSide1() << "-" << it.GetSide2() << " | ";
        if (counter% 6==0) {
            cout << endl;
           
        }
    }

    cout << endl << endl << endl;
    cout << "                                        engine tile" << endl;
    cout << "                                           " << engineTile.GetSide1()<< endl;
    cout << "                                           " << "|" << endl;
    cout << "                                           " << engineTile.GetSide2() << endl;

    cout << endl << endl << endl;
    cout << " Computer Tiles:" << endl;
    counter = 0;
    for (auto& it : computerTiles) {
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

void Round::MakeUserMoves()
{
    int tilenumber;
    cout << "please enter the tile(1-16) you want to pick" << endl;
    cin >> tilenumber;
    char train;
    cout << "please enter the Train(U-user,C-computer,M-mexican) you want to pick" << endl;
    cin >> train;

}

void Round::MakeComputerMoves()
{
    cout << "computer should choose the best move!" << endl;
}
