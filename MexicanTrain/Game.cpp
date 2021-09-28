/*
************************************************************
* Name:  Bishal Thapa									   *
* Project:  Project 1 Mexican Train C++				       *
* Class:  CMPS366 OPL				                       *
* Date:  09/27/2020				                           *
************************************************************
*/


#include "Game.h"
void Game::StartGame()
{
    bool stopgame = false;
    bool computertrainmarked=false;
    bool usertrainmarked=false;
    string gameinput = "X";
    Round* newround;

    //input validation
    while (gameinput != "S" && gameinput != "L") {
        cout << "1)Press S to start new game" << endl;
        cout << "2) Press L to load saved game from file" << endl;
        cout << "-----------------------------------------------------" << endl;
        cout << ">>";
        cin >> gameinput;
    }

    if (gameinput == "L") {
        
        //read from file and initialize
        string line;
        string filename;

       
        cout << "enter the file name to load game from (without.txt)" << endl;
        cin >> filename;
        filename = filename + ".txt";

        //filename validation that cheks filename is not empty 
        while (filename.length() < 6) {
            cout << "Invalid filename reenter" << endl;
            cin >> filename;
            filename = filename + ".txt";
        }

        ifstream myfile(filename);

        if (myfile.is_open())
        {
            //Reading contents of the text file line by line and storing it.
            //////////////////////////////////current round//////////////////////////////////////
            getline(myfile, line);
            currentround = stoi(line.substr(7));
            //next two line are not useful for storing data.           
            getline(myfile, line);
            getline(myfile, line);
            getline(myfile, line);
           
            ////////////////////////////////////computer score///////////////////////////////////////
            computerscore = stoi(line.substr(10));
            //addComputerscore(computerscore);

            ////////////////////////////////////////COMPUTERS TILES///////////////////////////////////////////
            vector<string> computertilesunrefined;
            vector<Tile> computerrefined;
           
            getline(myfile, line);
            //splitting the tiles from the line
            LineSplitter(TrimSpace(line), computertilesunrefined);
            
            //there is 3 spaces and Hand:  before tiles so 4 spaces are hold by those
            for (int i = 1; i < computertilesunrefined.size(); i++) {
                Tile mytile= Tile( stoi(computertilesunrefined[i].substr(0,1)), stoi(computertilesunrefined[i].substr(2)));
                computerrefined.push_back(mytile);
            }

            ///////////////////////////////COMPUTER TRAIN//////////////////////////////////////////////////////
            getline(myfile, line);
            vector<string> computertrainunrefined;
            vector<Tile> computertrainrefined;
            LineSplitter(TrimSpace(line) , computertrainunrefined);

            
            //O element is doesnot have anytiles so start to read from index'1'
            int startpos = 1;
            //if index 1 has M that means train is marked
            if (computertrainunrefined[1] == "M") {
                startpos =startpos+1;
                computertrainmarked = true;
            }
         
            //start pos depends on if the train was marked or not.
            for (int i = startpos; i < computertrainunrefined.size(); i++) {
                Tile mytile = Tile(stoi(computertrainunrefined[i].substr(2)), stoi(computertrainunrefined[i].substr(0, 1)));
                computertrainrefined.push_back(mytile);
            }

            //getting 2 more lines until we get human score
            getline(myfile, line);
            //there was one extra line on one of the serilizaation file. so If current line is empty get one more line
            if (line.empty()) {
                getline(myfile, line);
            }
            getline(myfile, line);
           
            //////////////////////user score///////////////////////////////////////////////////////
            
            //user score is found after index 10 in serialization file.
            userscore = stoi(line.substr(10));
            //addUserscore(userscore);
           
            //////////////////////////////getting user player tiles.///////////////////////////////////////////
            
            vector<string> userstilesunrefined;
            vector<Tile> userstilerefined;
            
            getline(myfile, line);

            //splitting the tiles from the line
            LineSplitter(TrimSpace(line), userstilesunrefined);
            
            //there is 1 space for Hand:  before tiles start.
            for (int i = 1; i < userstilesunrefined.size(); i++) {
                Tile mytile = Tile(stoi(userstilesunrefined[i].substr(0, 1)), stoi(userstilesunrefined[i].substr(2)));
                userstilerefined.push_back(mytile);
            }
   
            //////////////////////FOR USER TRAIN//////////////////////////////////////////////////////////////
            
            getline(myfile, line);
            vector<string> usertrainunrefined;
            vector<Tile> usertrainrefined;
            LineSplitter(TrimSpace(line), usertrainunrefined);

            //endpos is the last element of the vector
            int endpos = usertrainunrefined.size()-1;

            //if last element is M donot take last element as a tile.
            if (usertrainunrefined[endpos] == "M") {
                usertrainmarked = true;
                endpos = endpos - 1;
            }
            
            //All the elements from 1 to endpos are valid tiles.
            for (int i = 1; i <= endpos; i++) {
                Tile mytile = Tile(stoi(usertrainunrefined[i].substr(0, 1)), stoi(usertrainunrefined[i].substr(2)));
                usertrainrefined.push_back(mytile);
            }

            ////////////////////////////////FOR MEXICAN TRAIN/////////////////////////////////////////////////////////////
            //next line is going to be empty
            getline(myfile, line);
            getline(myfile, line);

            vector<string> mexicantrainunrefined;
            vector<Tile> mexicantrainrefined;

            LineSplitter(TrimSpace(line), mexicantrainunrefined);

            //there are two spaces before the tiles start in this case.

            for (int i = 2; i < mexicantrainunrefined.size(); i++) {
                Tile mytile = Tile(stoi(mexicantrainunrefined[i].substr(0, 1)), stoi(mexicantrainunrefined[i].substr(2)));
                mexicantrainrefined.push_back(mytile);
            }
            
            ////////////////////////////////////////FOR BONEYARD TILES////////////////////////////////////////////
            //next line is useless for the data.
            getline(myfile, line);
            getline(myfile, line);

            vector<string> boneyardunrefined;
            vector<Tile> boneyardrefined;
            LineSplitter(TrimSpace(line), boneyardunrefined);

            //there is 1 space before the tiles start
            for (int i = 1; i < boneyardunrefined.size(); i++) {
                Tile mytile = Tile(stoi(boneyardunrefined[i].substr(0, 1)), stoi(boneyardunrefined[i].substr(2)));
                boneyardrefined.push_back(mytile);
            }
            ////////////////////////////////////////////FOR CHECKING NEXT PLAYERS TURN///////////////////////////////////
            //next line is useless for data retreiving.
            getline(myfile, line);
            getline(myfile, line);
            vector<string> nextplayer;

            LineSplitter(TrimSpace(line), nextplayer);

            if (nextplayer[2] == "Human") {
                setUserfirst(true);
            }
            else if (nextplayer[2] == "Computer") {
                setUserfirst(false);
            }
            else {
                cout << "file format error" << endl;
            }

            myfile.close();
            //if we have come this far it is time to initialize game using the data we retreived from the text file.
            newround = new Round(currentround);
            newround->InitializefromFile(usertrainrefined, computertrainrefined,mexicantrainrefined, usertrainmarked, computertrainmarked, boneyardrefined, userstilerefined,computerrefined);
            setInitializedfromFile(true);
        }
        else {
            cout << "Unable to open file or invalid filename. Please restart";
            return;
        }    
    }
    else { 
        newround = new Round(currentround);
        newround->Initializegame();
    }

    
    //reading from file is done now. So the game is loaded or the new game is initialized if not game exists.
    while (!stopgame) {

        //for storing user score during toss
        int toss = -1;
     
        //if initialized from file, no need to worry about the user who goes next.
        if (isInitializedfromFile()) {
            if (isUserfirst()) {
                cout << "Human saved as next from the serailized filed" << endl;
            }
            else {
                cout << "computer saved as next from the serailized filed" << endl;
            }
        }
        
        //if not initialized from file and no winner as of now do a toss
        else if (computerscore == userscore && !isInitializedfromFile())
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
                setUserfirst(true);
                cout << "You won the toss! Go first." << endl;

            }
            else
            {
                setUserfirst(false);
                cout << "Computer won the toss! Computer goes first" << endl;
            }
            cout << "_____________________________________________________________" << endl;
        }

        //if user score is already stored and computer has more score means computer goes first.
        else if (computerscore < userscore)
        {
            setUserfirst(false);
            cout << "Computer goes first as computer is trailing behind in the score!" << endl;
        }
        //user goes first
        else
        {
            setUserfirst(true);
            cout << "Human player goes first as User is trailing behind in the score!" << endl;
        }

        //Round object that holds vlaues of a particular round.
        //Initialized the tiles and trains for the new round.
        //starts the game for the new round.this countinues until the game is over.
       
        bool playmore= newround->PlayMoves(isUserfirst(),currentround,getUserscore(),getComputerscore());

        //In this case game has been serialized so needs to be ended.
        if (!playmore) {
            return;
        }

        //adds round score to the game score
        addComputerscore(newround->computerRoundscore());
        addUserscore(newround->playerRoundscore());

        ///------------------------------Displaying the user score--------------------------------///
        cout << "--------------------------------------------------------" << endl;
        cout << "The total score for human player is:" << getUserscore() << endl;
        cout << "The total score for computer player is:" << getComputerscore() << endl;
        cout << "--------------------------------------------------------" << endl;
        
        //This runs once the game is over.
        //using string for input rather than char so that if user enters string program doesnot runs the loop multiple times.
        string input;
        do
        {

            cout << "Do you want to play another game? PRESS 'Y' or 'N'" << endl;
            cout << ">>";
            cin >> input;

            //Help taken from https://stackoverflow.com/questions/5864540/infinite-loop-with-cin-when-typing-string-while-a-number-is-expected
            //this helps for input validation and handles string input for the number. 
            if (cin.fail())
            {
                cout << "ERROR -- You entered an invalid input!!!";
                // get rid of failure state
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                input = "X";
            }

        } while (input!="Y" && input!="N");

        if (input == "N")
        {
            stopgame = true;
            cout << "___________________________________________________" << endl;
            if (getUserscore() < getComputerscore()) {
                cout << "Human player won the game" << endl;
            }
            else if(getUserscore() > getComputerscore()) 
            {
                cout << "Computer player won the game" << endl;
            }
            else {
                cout << "Game tied" << endl;
            }
            cout << "___________________________________________________" << endl;
        }
        else if(input=="Y") {
            currentround++;
            //start a new round here;
            newround = new Round(currentround);
            newround->Initializegame();
        }
       
    }
}


void Game::LineSplitter(string str, vector<string> & vect)
{
    string tile = "";
    for (auto x : str)
    {
        if (x == ' ')
        {
            vect.push_back(tile);
            tile = "";
        }
        else {
            tile = tile + x;
        }
    }
    vect.push_back(tile);
   
}

//Help taken from https://www.techiedelight.com/trim-string-cpp-remove-leading-trailing-spaces/
string Game::TrimSpace(string& line)
{
    auto start = line.begin();
    while (start != line.end() && isspace(*start)) {
        start++;
    }

    auto end = line.end();
    do {
        end--;
    } while (distance(start, end) > 0 && isspace(*end));

    return string(start, end + 1);
}