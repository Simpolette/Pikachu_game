#include "Player.h"

bool checkAvailableUserName(vector <Player*> list, string userName)
{
    // Check if username is in list or not using linear search
    int listSize = list.size();
    for (int i = 0; i < listSize; i++)
    {
        if (list[i]->userName == userName)
        {
            return false;
        }
    }
    return true;
}

bool checkCorrectAccount(vector <Player*> list, string userName, string password)
{   
    // Check if player input the correct username and password
    int listSize = list.size();
    for (int i = 0; i < listSize; i++)
    {
        if (list[i]->userName == userName)
        {
            // if username is correct then we don't need to check any others bcs username is unique
            if (list[i]->password == password)
                return true;
            return false;
        }
    }
    return false;
}

void addNewPlayerToList(vector <Player*>& list, string userName, string password, Board gameBoard)
{
    Player* newPlayer = new Player;
    newPlayer->userName = userName;
    newPlayer->password = password;
    newPlayer->Easy = new InforMatches(gameBoard.row, gameBoard.col);
    newPlayer->Hard = new InforMatches(gameBoard.row, gameBoard.col);
    newPlayer->Memory = new InforMatches(gameBoard.row, gameBoard.col);

    list.push_back(newPlayer);
    // Add new player in to vector list
}

int posPlayerInList(vector <Player*>& list, string userName)
{
    // Get the current player position in the list
    int listSize = list.size();
    for (int i = 0; i < listSize; i++)
    {
        if (list[i]->userName == userName)
            return i;
    }
    return 0;
}

void copyBoardEasy(vector <Player*> list, int pos, int** board, Board gameBoard)
{
    // Copy board from game playing to list board for saved games
    for (int i = 0; i < gameBoard.row; i++)
    {
        for (int j = 0; j < gameBoard.col; j++)
        {
            list[pos]->Easy->board[i][j] = board[i + 1][j + 1];
        }
    }
}

void copyBoardHard(vector <Player*> list, int pos, int** board, Board gameBoard)
{
    // Copy board from game playing to list board for saved games
    for (int i = 0; i < gameBoard.row; i++)
    {
        for (int j = 0; j < gameBoard.col; j++)
        {
            list[pos]->Hard->board[i][j] = board[i + 1][j + 1];
        }
    }
}

void copyBoardMemory(vector <Player*> list, int pos, int** board, Board gameBoard)
{
    // Copy board from game playing to list board for saved games
    for (int i = 0; i < gameBoard.row; i++)
    {
        for (int j = 0; j < gameBoard.col; j++)
        {
            list[pos]->Memory->board[i][j] = board[i + 1][j + 1];
        }
    }
}

void copyBoard(int** mainBoard, int** board, Board gameBoard)
{
    // Copy board from saved games to ingame board
    for (int i = 1; i < gameBoard.row + 1; i++)
    {
        for (int j = 1; j < gameBoard.col + 1; j++)
        {
            mainBoard[i][j] = board[i - 1][j - 1];
        }
    }
}

void outputInfoPlayer(vector<Player*> list, string nameFile, Board gameBoard)
{
    // Print out all of the player info to get the saved games on another file with the following format:
    // <username> ,<password>, <bestScoreEasy> <bestTimeEasy> <scoreEasy> <pokemonEasy> <timeEasy> <shuffleCountEasy> <gameSavedCheckEasy> 
    // (This is not a new line) <bestScoreHard> <bestTimeHard> <scoreHard> <pokemonHard> <timeHard> <shuffleCountHard> <gameSavedCheckHard> 
    // (This is not a new line) <bestScoreMemory> <bestTimeMemory> <scoreMemory> <pokemonMemory> <timeMemory> <shuffleCountMemory> <gameSavedCheckMemory>
    // Boardsaved for Easy sized 5 * 8
    // Boardsaved for Hard sized 5 * 8
    // Boardsaved for Memory sized 5 * 8
    // For more details check the "Player.txt" file
    ofstream outFile(nameFile);
    int listSize = list.size();
    for (int i = 0; i < listSize; i++) {
        // if (list[i]->userName == " ") continue;
        outFile << list[i]->userName << "," << " ";
        outFile << list[i]->password << "," << " ";

        outFile << list[i]->Easy->bestScore << " ";
        outFile << list[i]->Easy->bestTime << " ";
        outFile << list[i]->Easy->score << " ";
        outFile << list[i]->Easy->pokemon << " ";
        outFile << list[i]->Easy->time << " ";
        outFile << list[i]->Easy->shuffleCount << " ";
        outFile << list[i]->Easy->gameSavedCheck << " ";

        outFile << list[i]->Hard->bestScore << " ";
        outFile << list[i]->Hard->bestTime << " ";
        outFile << list[i]->Hard->score << " ";
        outFile << list[i]->Hard->pokemon << " ";
        outFile << list[i]->Hard->time << " ";
        outFile << list[i]->Hard->shuffleCount << " ";
        outFile << list[i]->Hard->gameSavedCheck << " ";

        outFile << list[i]->Memory->bestScore << " ";
        outFile << list[i]->Memory->bestTime << " ";
        outFile << list[i]->Memory->score << " ";
        outFile << list[i]->Memory->pokemon << " ";
        outFile << list[i]->Memory->time << " ";
        outFile << list[i]->Memory->shuffleCount << " ";
        outFile << list[i]->Memory->gameSavedCheck << " ";

        outFile << endl;

        // Output boards for each mode
        // Note: No edge
        for (int u = 0; u < gameBoard.row; u++)
        {
            for(int v = 0; v < gameBoard.col; v++)
            {
                outFile << list[i]->Easy->board[u][v] << " ";
            }
            outFile << endl;
        }

        for (int u = 0; u < gameBoard.row; u++)
        {
            for(int v = 0; v < gameBoard.col; v++)
            {
                outFile << list[i]->Hard->board[u][v] << " ";
            }
            outFile << endl;
        }

        for (int u = 0; u < gameBoard.row; u++)
        {
            for(int v = 0; v < gameBoard.col; v++)
            {
                outFile << list[i]->Memory->board[u][v] << " ";
            }
            outFile << endl;
        }
    }
}

void loadInfoPlayer(vector<Player*>& list, string nameFile, Board gameBoard)
{    
    // Read file to get all of info player and load into list
    ifstream inFile(nameFile);
    string line;
    while (getline(inFile, line)) {
        Player* newPlayer = new Player;
        newPlayer->Easy = new InforMatches(gameBoard.row, gameBoard.col);
        newPlayer->Hard = new InforMatches(gameBoard.row, gameBoard.col);
        newPlayer->Memory = new InforMatches(gameBoard.row, gameBoard.col);
        
        istringstream iss(line);
        string username, password;
        getline(iss, username, ',');
        iss.ignore();
        getline(iss, password, ',');
        iss.ignore();
        if (!username.empty()) {
            newPlayer->userName = username;
            newPlayer->password = password;
            iss >> newPlayer->Easy->bestScore >> newPlayer->Easy->bestTime;
            iss >> newPlayer->Easy->score >> newPlayer->Easy->pokemon >> newPlayer->Easy->time;
            iss >> newPlayer->Easy->shuffleCount >> newPlayer->Easy->gameSavedCheck;

            iss >> newPlayer->Hard->bestScore >> newPlayer->Hard->bestTime;
            iss >> newPlayer->Hard->score >> newPlayer->Hard->pokemon >> newPlayer->Hard->time;
            iss >> newPlayer->Hard->shuffleCount >> newPlayer->Hard->gameSavedCheck;

            iss >> newPlayer->Memory->bestScore >> newPlayer->Memory->bestTime;
            iss >> newPlayer->Memory->score >> newPlayer->Memory->pokemon >> newPlayer->Memory->time;
            iss >> newPlayer->Memory->shuffleCount >> newPlayer->Memory->gameSavedCheck;

            string lineBoard;
            // Read board for each mode
            for (int i = 0; i < gameBoard.row; i++)
            {
                getline(inFile, lineBoard);
                istringstream ssline(lineBoard);
                for (int j = 0; j < gameBoard.col; j++)
                {
                    ssline >> newPlayer->Easy->board[i][j];
                }
            }

            for (int i = 0; i < gameBoard.row; i++)
            {
                getline(inFile, lineBoard);
                istringstream ssline(lineBoard);
                for (int j = 0; j < gameBoard.col; j++)
                {
                    ssline >> newPlayer->Hard->board[i][j];
                }
            }

            for (int i = 0; i < gameBoard.row; i++)
            {
                getline(inFile, lineBoard);
                istringstream ssline(lineBoard);
                for (int j = 0; j < gameBoard.col; j++)
                {
                    ssline >> newPlayer->Memory->board[i][j];
                }
            }
            list.push_back(newPlayer);
        }
        else
        {
            delete newPlayer;
        }
    }
    inFile.close();
}

bool comparePlayerScoreEasy(Player* p1, Player* p2)
{
    // Config type of sort for sorting algorithm
    return (p1->Easy->bestScore > p2->Easy->bestScore);
}

bool comparePlayerScoreHard(Player* p1, Player* p2)
{
    // Config type of sort for sorting algorithm
    return (p1->Hard->bestScore > p2->Hard->bestScore);
}

bool comparePlayerScoreMemory(Player* p1, Player* p2)
{
    // Config type of sort for sorting algorithm
    return (p1->Memory->bestScore > p2->Memory->bestScore);
}

void sortPlayerScoreEasy(vector <Player*> list)
{
    // Sort player score and print out to console the highest 3
    sort(list.begin(), list.end(), comparePlayerScoreEasy);
    int listSize = list.size();
    for (int i = 0; i < 3 && i < listSize; i++)
    {
        if (list[i]->Easy->bestScore == 0)
            break;
        // If reached 0 then there is no used checking
        gotoxy(68, 13 + i * 3);
        cout << i + 1 << ". " << list[i]->userName;
        gotoxy(108, 13 + i * 3);
        cout << list[i]->Easy->bestScore;
    }
}

void sortPlayerScoreHard(vector <Player*> list)
{
    // Sort player score and print out to console the highest 3
    sort(list.begin(), list.end(), comparePlayerScoreHard);
    int listSize = list.size();
    for (int i = 0; i < 3 && i < listSize; i++)
    {
        if (list[i]->Hard->bestScore == 0)
            break;
        // If reached 0 then there is no used checking
        gotoxy(68, 13 + i * 3);
        cout << i + 1 << ". " << list[i]->userName;
        gotoxy(108, 13 + i * 3);
        cout << list[i]->Hard->bestScore;
    }
}

void sortPlayerScoreMemory(vector <Player*> list)
{
    // Sort player score and print out to console the highest 3
    sort(list.begin(), list.end(), comparePlayerScoreMemory);
    int listSize = list.size();
    for (int i = 0; i < 3 && i < listSize; i++)
    {
        if (list[i]->Memory->bestScore == 0)
            break;
        // If reached 0 then there is no used checking
        gotoxy(68, 13 + i * 3);
        cout << i + 1 << ". " << list[i]->userName;
        gotoxy(108, 13 + i * 3);
        cout << list[i]->Memory->bestScore;
    }
}

bool comparePlayerTimeEasy(Player* p1, Player* p2)
{
    // Config type of sort for sorting algorithm
    return (p1->Easy->bestTime < p2->Easy->bestTime);
}

bool comparePlayerTimeHard(Player* p1, Player* p2)
{
    // Config type of sort for sorting algorithm
    return (p1->Hard->bestTime < p2->Hard->bestTime);
}

bool comparePlayerTimeMemory(Player* p1, Player* p2)
{
    // Config type of sort for sorting algorithm
    return (p1->Memory->bestTime < p2->Memory->bestTime);
}

void sortPlayerTimeEasy(vector <Player*> list)
{
    // Sort player time and print out to console the fastest 3
    sort(list.begin(), list.end(), comparePlayerTimeEasy);
    int listSize = list.size();
    int cnt = 0;
    for (int i = 0; cnt < 3 && i < list.size(); i++)
    {
        if (list[i]->Easy->bestTime == 0) continue;
        // Player time is sorted from smallest to highest, 0 will definitely be smallest so we will skip until meet an acceptable value
        gotoxy(8, 13 + cnt * 3);
        cout << cnt + 1 << ". " << list[i]->userName;
        gotoxy(47, 13 + cnt * 3);
        cnt++;
        cout << list[i]->Easy->bestTime << "s";
    }
}

void sortPlayerTimeHard(vector <Player*> list)
{
    // Sort player time and print out to console the fastest 3
    sort(list.begin(), list.end(), comparePlayerTimeHard);
    int listSize = list.size();
    int cnt = 0;
    for (int i = 0; cnt < 3 && i < list.size(); i++)
    {
        if (list[i]->Hard->bestTime == 0) continue;
        // Player time is sorted from smallest to highest, 0 will definitely be smallest so we will skip until meet an acceptable value
        gotoxy(8, 13 + cnt * 3);
        cout << cnt + 1 << ". " << list[i]->userName;
        gotoxy(47, 13 + cnt * 3);
        cnt++;
        cout << list[i]->Hard->bestTime << "s";
    }
}

void sortPlayerTimeMemory(vector <Player*> list)
{
    // Sort player time and print out to console the fastest 3
    sort(list.begin(), list.end(), comparePlayerTimeMemory);
    int listSize = list.size();
    int cnt = 0;
    for (int i = 0; cnt < 3 && i < list.size(); i++)
    {
        if (list[i]->Memory->bestTime == 0) continue;
        // Player time is sorted from smallest to highest, 0 will definitely be smallest so we will skip until meet an acceptable value
        gotoxy(8, 13 + cnt * 3);
        cout << cnt + 1 << ". " << list[i]->userName;
        gotoxy(47, 13 + cnt * 3);
        cnt++;
        cout << list[i]->Memory->bestTime << "s";
    }
}

void deleteList(vector <Player*> list)
{
    int listSize = list.size();
    for (int i = 0; i < listSize; i++)
    {
        delete list[i];
    }
}