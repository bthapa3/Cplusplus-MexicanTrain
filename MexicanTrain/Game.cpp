#include "Game.h"

void Game::startGame()
{
    bool stopgame = false;
    char input;
    while (!stopgame) {

        char toss;
        if (computerscore == userscore)
        {
            do 
            {
                cout << "TOSS:  Please choose 0- for head or 1- for tails " << endl;
                cin >> toss;
            } while (toss!='0' && toss!='1');


            srand((unsigned)time(0));
            int randomNumber = (rand() % 2);

            cout << "Toss value: " << randomNumber << endl;
            if ((randomNumber == 0 && toss == '0') || (randomNumber == 1 && toss == '1'))
            {
                userfirst = true;
                cout << "You won the toss! Go first." << endl;
            }
            else
            {
                userfirst = false;
                cout << "Computer won the toss! Computer goes first" << endl;
            }
        }
        else if (computerscore< userscore)
        {
            userfirst = false;
            cout << "Computer goes first as computer is trailing behind in the score!" << endl;
        }
        else 
        {
            userfirst = true;
            cout << "User goes first as User is trailing behind in the score!" << endl;
        }

        Round *newround =new Round(currentround);
        newround->Initializegame();
        

       // while (true) 
        //{
        newround->DisplayGame();
            //newround->PlayMoves();
            //newround->MakeComputerMoves();
        
        //}

        cout << "Do you want to play another game? Else press anyother key";
        cin >> input;
        if (input != 'y') 
        {
            stopgame = true;
        }
        else {
            currentround++;
        }
    }
}
