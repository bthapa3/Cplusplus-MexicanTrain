#include "Game.h"

void Game::startGame()
{
    bool stopgame = false;
    char input;
    while (!stopgame) {

        int toss = -1;
        if (computerscore == userscore)
        {
            //This does the player toss when the game is started
            // For the next rounds the players with lower score goes first.
            do
            {

                cout << "Choose 0 for heads and 1 for tails" << endl;
                cout << ">>";
                cin >> toss;


                //Help taken from https://stackoverflow.com/questions/5864540/infinite-loop-with-cin-when-typing-string-while-a-number-is-expected
                //this helps for input validation and handles string input for the number. 
                if (cin.fail())
                {
                    cout << "ERROR -- You entered an invalid input!!!";

                    // get rid of failure state
                    cin.clear();

                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    toss = -1;
                }

            } while (toss > 1 || toss < 0);


            srand((unsigned)time(0));
            int randomNumber = (rand() % 2);
            cout << "_____________________________________________________________" << endl;
            cout << "Your input: " << toss << " Toss value: " << randomNumber << endl;
            cout << "_____________________________________________________________" << endl;
            if ((randomNumber == 0 && toss == 0) || (randomNumber == 1 && toss == 1))
            {
                userfirst = true;
                cout << "You won the toss! Go first." << endl;

            }
            else
            {
                userfirst = false;
                cout << "Computer won the toss! Computer goes first" << endl;
            }
            cout << "_____________________________________________________________" << endl;
        }
        else if (computerscore < userscore)
        {
            userfirst = false;
            cout << "Computer goes first as computer is trailing behind in the score!" << endl;
        }
        else
        {
            userfirst = true;
            cout << "User goes first as User is trailing behind in the score!" << endl;
        }

        //Round object that holds vlaues of a particular round.
        Round* newround = new Round(currentround);
        //Initialized the tiles and trains for the new round.
        newround->Initializegame();
        //starts the game for the new round.this countinues until the game is over.
        newround->PlayMoves(userfirst);

        //This runs once the game is over.
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


