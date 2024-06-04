#include "Gameplay.h"

void createBoard(int**& board, Board gameBoard) 
{
    // Allocate a board matrix and assign it with 0
    board = new int* [gameBoard.row + 2];
    for (int i = 0; i < gameBoard.row + 2; i++)
    {
        board[i] = new int[gameBoard.col + 2];
        for (int j = 0; j < gameBoard.col + 2; j++)
        {
            board[i][j] = 0;
        }
    }
}

void createPoint(int**& board, Board gameBoard) 
{
    // Generate board filled with pokemons
    for (int i = 1; i < gameBoard.row + 1; i++)
    {
        for (int j = 1; j < gameBoard.col + 1; j++)
        {
            if (board[i][j] == 0) // Check if a pokemon has been created here bcs of random
            {
                board[i][j] = rand() % 15 + 65; // Random a character from 'A' to 'O'
                int x = rand() % gameBoard.row + 1; 
                int y = rand() % gameBoard.col + 1; 
                while (board[x][y] != 0 || (i == x && j == y)) // Check if position is empty or not
                {
                    x = rand() % gameBoard.row + 1;
                    y = rand() % gameBoard.col + 1;
                }
                board[x][y] = board[i][j]; 
            }
        }
    }
}

string* createBackground()
{
    // Allocate memory for the background
	string* background = new string[26];
    return background;
}

void getBackground(string fileName, string* background)
{
    // Read the background from the fileName
	fstream fs;
    fs.open(fileName, fstream::in);
    int i = 0;
    while (!fs.eof()){
        getline(fs, background[i]);
        i++;
    }
}

void deletePoint(int** board, Pokemon p1, Pokemon p2, int mode)
{
    // Delete after 2 pokemons have been matched 
    if (mode == EASY)
    { //EASY MODE
        board[p1.i][p1.j] = 0;
        board[p2.i][p2.j] = 0;
        return;
        // Pokemon stays at the same position on EASY mode so just need to erase at the position
    }
    else
    {
        board[p1.i][p1.j] = 0;
        board[p2.i][p2.j] = 0;
        int gameBoardCol = 8;
        //HARD MODE
        for (int j = p1.j; j <= gameBoardCol; j++)
        {
            board[p1.i][j] = board[p1.i][j + 1];
        }
        // Move every pokemons one index to the left from erased pokemon
        if (p1.i == p2.i && p1.j < p2.j) 
            p2.j--;
        // Check if 2 pokemons is in the same row and p1 position is before p2
        // If then has to subtract the p2 col count by 1 for correct display of position
        for (int j = p2.j; j <= gameBoardCol; j++)
        {
            board[p2.i][j] = board[p2.i][j + 1];
        }
        // Move every pokemons one index to the left from erased pokemon

        // // LINKEDLIST MODE
        // removePokemonHard(board, p1.i, p1.j);
        // if (p1.i == p2.i && p1.j < p2.j) 
        //     p2.j--;
        // // Check if 2 pokemons is in the same row and p1 position is before p2
        // // If then has to subtract the p2 col count by 1 for correct display of position
        // removePokemonHard(board, p2.i, p2.j);
    }
}

bool validPoke(int** board, Pokemon p1, Pokemon p2) 
{
    // Check if pokemon is the same type and is not at the same place or not
    if (board[p1.i][p1.j] != board[p2.i][p2.j])
        return false;
    if (p1.i == p2.i && p1.j == p2.j)
        return false;
    return true;
}

bool matchingI(int** board, Pokemon p1, Pokemon p2)
{
    if (p1.i == p2.i) // Check if p1 and p2 are on the same row
    {
        if (p1.j > p2.j) swap(p1.j, p2.j); // If p1 is to the right of p2 on the row, swap the positions of p1 and p2 to ensure that p1 is always to the left of p2, making the loop easier to run.
        for (int j = p1.j + 1; j < p2.j; j++) // Iterate through each cell on the row between p1 and p2.
        {
            if (board[p1.i][j] != 0) // If any cell along the path is not empty, it cannot be connected
                return false;
        }
        return true;
    }
    if (p1.j == p2.j) // Check if p1 and p2 are on the same column.
    {
        if (p1.i > p2.i) swap(p1.i, p2.i); // If p1 is below p2 on the column, swap the positions of p1 and p2 to ensure that p1 is always above p2
        for (int i = p1.i + 1; i < p2.i; i++)
        {
            if (board[i][p1.j] != 0) // If any cell along the path is not empty, it cannot be connected
                return false;
        }
        return true;
    }
    return false;
}

bool matchingL(int** board, Pokemon p1, Pokemon p2, Pokemon& corner)
{
    // Initialize 2 corner cells of the L-shape
    Pokemon temp1, temp2;
    temp1.i = p1.i, temp1.j = p2.j;
    temp2.i = p2.i, temp2.j = p1.j;
    if (board[temp1.i][temp1.j] != 0 && board[temp2.i][temp2.j] != 0) // Check if the 2 corner cells have the same value of 0, if so, return false
        return false;
    // check matching I for two cases of L matching
    bool path_1_1 = matchingI(board, p1, temp1);
    bool path_1_2 = matchingI(board, p2, temp1);

    bool path_2_1 = matchingI(board, p1, temp2);
    bool path_2_2 = matchingI(board, p2, temp2);

    if (path_1_1 && path_1_2 && board[temp1.i][temp1.j] == 0) // Check if it's possible to create 2 paths from I to the first corner cell, and the first corner cell contains the value 0
    {
        // Initialize the pixel based on the index of the corner on the game board
        corner = temp1;
        corner.x = STARTING_X + (corner.j - 1) * CELLS_WIDTH;
        corner.y = STARTING_Y + (corner.i - 1) * CELLS_HEIGHT;
        return true;
    }
    if (path_2_1 && path_2_2 && board[temp2.i][temp2.j] == 0) // Check if it's possible to create 2 paths from I to the second corner cell, and the second corner cell contains the value 0
    {
        // Initialize the pixel based on the index of the corner on the game board
        corner = temp2;
        corner.x = STARTING_X + (corner.j - 1) * CELLS_WIDTH;
        corner.y = STARTING_Y + (corner.i - 1) * CELLS_HEIGHT;
        return true;
    }

    return false;
}

bool matchingUZ(int** board, Pokemon& p1, Pokemon& p2, Pokemon& corner1, Pokemon& corner2, Board gameBoard)
{
    // 2 corners in the same row
    if (p1.i > p2.i)
        swap(p1, p2); // p1 higher than p2, swap them

    for (int i = p1.i + 1; i != p1.i; i++)
    {
        if (i > gameBoard.row + 1)
            i = 0; // If i exceeds the row index on the board, return to the first row
        Pokemon temp1, temp2; // Create two temporary variables to store the coordinates of two potential corner cells
        temp1.i = i, temp1.j = p1.j;
        temp2.i = i, temp2.j = p2.j;
        // Check if it's possible to create connections from p1 to temp1, from p2 to temp2, and from temp1 to temp2.
        if (board[temp1.i][temp1.j] == 0 && board[temp2.i][temp2.j] == 0)
        {
            bool path_1 = matchingI(board, p1, temp1);
            bool path_2 = matchingI(board, p2, temp2);
            bool path_3 = matchingI(board, temp1, temp2);

            if (path_1 && path_2 && path_3) // If 3 paths are all satisfied 
            {
                // Initialize the pixel based on the index of the corner on the game board
                corner1 = temp1;
                corner1.x = STARTING_X + (corner1.j - 1) * CELLS_WIDTH;
                corner1.y = STARTING_Y + (corner1.i - 1) * CELLS_HEIGHT;

                corner2 = temp2;
                corner2.x = STARTING_X + (corner2.j - 1) * CELLS_WIDTH;
                corner2.y = STARTING_Y + (corner2.i - 1) * CELLS_HEIGHT;
                return true;
            }
        }
    }

    // 2 corners in the same column
    if (p1.j > p2.j)
        swap(p1, p2); //p1 on left side, p2 on right side

    for (int j = p1.j + 1; j != p1.j; j++)
    {
        if (j > gameBoard.col + 1)
            j = 0; // If j exceeds the column index on the board, return to the first column
        Pokemon temp1, temp2;
        temp1.i = p1.i, temp1.j = j;
        temp2.i = p2.i, temp2.j = j;
        // Check if it's possible to create connections from p1 to temp1, from p2 to temp2, and from temp1 to temp2.
        if (board[temp1.i][temp2.j] == 0 && board[temp2.i][temp2.j] == 0) 
        {
            bool path_1 = matchingI(board, p1, temp1);
            bool path_2 = matchingI(board, p2, temp2);
            bool path_3 = matchingI(board, temp1, temp2);
            if (path_1 && path_2 && path_3) // If the 3 paths are all satisfied 
            {
                // Initialize the pixel based on the index of the corner on the game board
                corner1 = temp1;
                corner1.x = STARTING_X + (corner1.j - 1) * CELLS_WIDTH;
                corner1.y = STARTING_Y + (corner1.i - 1) * CELLS_HEIGHT;

                corner2 = temp2;
                corner2.x = STARTING_X + (corner2.j - 1) * CELLS_WIDTH;
                corner2.y = STARTING_Y + (corner2.i - 1) * CELLS_HEIGHT;
                return true;
            }
        }
    }
    return false;
}

bool checkMatchingAndDisplay(int** board, Pokemon p1, Pokemon p2, int& point, Board gameBoard, string* background, int mode) //new function: adding point
{

    Pokemon corner;
    Pokemon corner1, corner2;
    bool valid = validPoke(board, p1, p2); // Check if the 2 Pokemons are valid
    bool checkI = matchingI(board, p1, p2);
    bool checkL = matchingL(board, p1, p2, corner);
    bool checkUZ = matchingUZ(board, p1, p2, corner1, corner2, gameBoard);
    if (valid)
    {
        if (checkI) // Check if the system can create an I-matching
        {
            point++;
            PlaySound(TEXT("Correct.wav"), NULL, SND_ASYNC); // Play sound if the 2 pokemon can be matched
            displayMatchingLine(p1, p2, true); // Display the matching line
            background_upgrade_line(p1, p2, background, mode); // Redraw the line but with the background
            return true;
        }
        if (checkL) // Check if the system can create an L-matching
        {
            point += 3;
            PlaySound(TEXT("Correct.wav"), NULL, SND_ASYNC); // Play sound if the 2 pokemon can be matched
            displayMatchingLineL(p1, p2, corner);
            background_upgrade_line(p1, corner, background, mode); // Redraw the line but with the background
            background_upgrade_line(p2, corner, background, mode); // Redraw the line but with the background
            return true;
        }
        if (checkUZ) // Check if the system can create an U-matching or Z-matching
        {
            point += 5;
            PlaySound(TEXT("Correct.wav"), NULL, SND_ASYNC); // Play sound if the 2 pokemon can be matched
            displayMatchingLineUZ(p1, p2, corner1, corner2, gameBoard);
            background_upgrade_line(p1, corner1, background, mode); // Redraw the line but with the background
            background_upgrade_line(corner1, corner2, background, mode); // Redraw the line but with the background
            background_upgrade_line(p2, corner2, background, mode); // Redraw the line but with the background
            return true;
        }
    }
    return false;
}

bool checkMatching(int** board, Pokemon p1, Pokemon p2, Board gameBoard) 
{
    // Check if whether 2 pokemons can be matched by any type of matching or not
    Pokemon corner;
    Pokemon corner1, corner2;
    if (validPoke(board, p1, p2)) // Check if 2 pokemons are the same type and on diffrent indices
    {
        if (matchingI(board, p1, p2))
            return true;
        if (matchingL(board, p1, p2, corner))
            return true;
        if (matchingUZ(board, p1, p2, corner1, corner2, gameBoard))
            return true;
    }
    return false;
}

bool checkContinue(int** board, Pokemon& p1, Pokemon& p2, Board gameBoard)
{
    // Using checkMatching function to check all possible pairs of pokemons
    // If met with one that satisfy, return that pair
    for (int i = 1; i < gameBoard.row + 1; i++)
    {
        for (int j = 1; j < gameBoard.col + 1; j++)
        {
            if (board[i][j] != 0)
            {
                for (int k = i; k < gameBoard.row + 1; k++)
                {
                    for (int l = 1; l < gameBoard.col + 1; l++)
                    {
                        if (board[i][j] == board[k][l] && (k != i || l > j))
                        {
                            p1.i = i;
                            p1.j = j;
                            p2.i = k;
                            p2.j = l;
                            if (checkMatching(board, p1, p2, gameBoard))
                                return true;
                        }
                    }
                }
            }
        }
    }
    return false;
}

void shuffleBoard(int** board, Board gameBoard) 
{
    // Shuffle everything using swap
    // Choose an existed pokemon, swap the position to an another existed pokemon
    // Do it for every cell on the board
    for (int i = 1; i < gameBoard.row + 1; i++){
        for (int j = 1; j < gameBoard.col + 1; j++){
            if (board[i][j] != 0)
            {   
                int randRow = 0, randCol = 0;
                while (board[randRow][randCol] == 0){
                    randRow = (rand() % gameBoard.row) + 1;
                    randCol = (rand() % gameBoard.col) + 1;
                }
                swap(board[i][j], board[randRow][randCol]);
            }
        }
    }
}

void Gameplay(int**& board, int mode, Board& gameBoard, vector <Player*> list, int playerPos)
{
NEW_GAME:
    // Initiate the gameBoard statistics
    gameBoard.col = 8;
    gameBoard.row = 5;
    gameBoard.width = gameBoard.col * CELLS_WIDTH;
    gameBoard.height = gameBoard.row * CELLS_HEIGHT;

    int pokemon;
    int count_space_bar = 0, score;
    int shuffleCount = 5;
    int i = 1, j = 1; // Current selected cell

    if (mode == EASY && list[playerPos]->Easy->gameSavedCheck == 1)
    {
        // Check what mode is being selected and is there a saved game or not
        int choice;
        displayContinueGame(choice); // Get the player choice on whether to continue the saved game or not
        if (choice == 1) // Player chose YES
        {
            // Copy all of saved game information to current game
            createBoard(board, gameBoard);
            copyBoard(board, list[playerPos]->Easy->board, gameBoard);
            score = list[playerPos]->Easy->score;
            pokemon = list[playerPos]->Easy->pokemon;
            shuffleCount = list[playerPos]->Easy->shuffleCount;
        }
        else // Player chose NO
        {   
            // Delete the saved game and create a new game
            list[playerPos]->Easy->gameSavedCheck = 0;
            goto NEW_GAME;
        }
    }
    else if (mode == HARD && list[playerPos]->Hard->gameSavedCheck == 1)
    {
        // Check what mode is being selected and is there a saved game or not
        int choice;
        displayContinueGame(choice); // Get the player choice on whether to continue the saved game or not
        if (choice == 1) // Player chose YES
        {
            // Copy all of saved game information to current game
            createBoard(board, gameBoard);
            copyBoard(board, list[playerPos]->Hard->board, gameBoard);
            score = list[playerPos]->Hard->score;
            pokemon = list[playerPos]->Hard->pokemon;
            shuffleCount = list[playerPos]->Hard->shuffleCount;
        }
        else // Player chose NO
        {
            // Delete the saved game and create a new game
            list[playerPos]->Hard->gameSavedCheck = 0;
            goto NEW_GAME;
        }
    }
    else // No saved game is found
    {
        Pokemon ignore1, ignore2;
        createBoard(board, gameBoard);
        createPoint(board, gameBoard);
        while (!checkContinue(board, ignore1, ignore2, gameBoard))
        {
            shuffleBoard(board, gameBoard);
            // Find a board that's playable for the player
        }
        pokemon = gameBoard.col * gameBoard.row;
        score = 0;
    }

    bool playloop = true;

    string* background = createBackground(); // Create the storage for background
    if (mode == EASY)
    {
        // Load the background based on mode
        getBackground("images/background_1.txt", background);
    }
    else if (mode == HARD)
    {
        // Load the background based on mode
        getBackground("images/background_2.txt", background);
    }

    system("cls");
    displayPlayerInfo(list, playerPos); // Display the player info: High score and Best time for each mode
    displayGameStatistic(); // Display a box for player current score and shuffle left of the playing game
    displayGameInstruction(); // Display small instruction for player to help player with the game
    updateShuffles(shuffleCount); // Update player current shuffle count
    displayGameBox(STARTING_X, STARTING_Y, gameBoard.height, gameBoard.width, board, gameBoard, background, mode); // Display entire gameboard, draw cell and character

    Pokemon pokemon1, pokemon2;
    pokemon1.x = -1; pokemon1.y = -1; pokemon1.i = -1; pokemon1.j = -1;
    pokemon2.x = -1; pokemon2.y = -1; pokemon2.i = -1; pokemon2.j = -1;

    int time_;
    time_ = time(0);
    // Store current timestamp starting to play in seconds

    while (playloop)
    {
        displayChosenBox(STARTING_X + (j - 1) * CELLS_WIDTH, STARTING_Y + (i - 1) * CELLS_HEIGHT, CELLS_HEIGHT, CELLS_WIDTH, (char)board[i][j], GREEN, WHITE);
        // Display current box choosing
        if (score < 0) score = 0;
        updateGameScore(score); // Update player current score
        int input = getConsoleInput(); // Get player input

        if (input == 2) // KEY_UP
        {
            TextColor(WHITE);
            if (board[i][j] != 0)
                displayChosenBox(STARTING_X + (j - 1) * CELLS_WIDTH, STARTING_Y + (i - 1) * CELLS_HEIGHT, CELLS_HEIGHT, CELLS_WIDTH, (char)board[i][j], BLACK, WHITE);
                // Delete the display of current box choosing
            else
            {
                int pX = STARTING_X + (j - 1) * CELLS_WIDTH;
                int pY = STARTING_Y + (i - 1) * CELLS_HEIGHT;
                background_upgrade(pX, pY, background, mode);
                // Get the coordinate to upgrade the background if there's no pokemon here
            }
            i--;
            if (i < 1) // Get to the other side of the row
                i = gameBoard.row;
            if (i == pokemon1.i && j == pokemon1.j) // Can't choose the box already selected unless player choose it the first time
                i--;
            if (i < 1) // Get to the other side of the row
                i = gameBoard.row;
        }

        else if (input == 5) // KEY_DOWN
        {
            TextColor(WHITE);
            if (board[i][j] != 0)
                displayChosenBox(STARTING_X + (j - 1) * CELLS_WIDTH, STARTING_Y + (i - 1) * CELLS_HEIGHT, CELLS_HEIGHT, CELLS_WIDTH, (char)board[i][j], BLACK, WHITE);
                // Delete the display of current box choosing
            else
            {
                int pX = STARTING_X + (j - 1) * CELLS_WIDTH;
                int pY = STARTING_Y + (i - 1) * CELLS_HEIGHT;
                background_upgrade(pX, pY, background, mode);
                // Get the coordinate to upgrade the background if there's no pokemon here
            }

            i++;
            if (i > gameBoard.row) // Get to the other side of the row
                i = 1;
            if (i == pokemon1.i && j == pokemon1.j) // Can't choose the box already selected unless player choose it the first time
                i++;
            if (i > gameBoard.row) // Get to the other side of the row
                i = 1;
        }

        else if (input == 3) // KEY_LEFT
        {
            TextColor(WHITE);
            if (board[i][j] != 0)
                displayChosenBox(STARTING_X + (j - 1) * CELLS_WIDTH, STARTING_Y + (i - 1) * CELLS_HEIGHT, CELLS_HEIGHT, CELLS_WIDTH, (char)board[i][j], BLACK, WHITE);
                // Delete the display of current box choosing
            else
            {
                int pX = STARTING_X + (j - 1) * CELLS_WIDTH;
                int pY = STARTING_Y + (i - 1) * CELLS_HEIGHT;
                background_upgrade(pX, pY, background, mode);
                // Get the coordinate to upgrade the background if there's no pokemon here
            }

            j--;
            if (j < 1) // Get to the other side of the column
                j = gameBoard.col; 
            if (i == pokemon1.i && j == pokemon1.j) // Can't choose the box already selected unless player choose it the first time
                j--;
            if (j < 1)
                j = gameBoard.col; // Get to the other side of the column
        }

        else if (input == 4) // KEY_RIGHT
        {
            TextColor(WHITE);
            if (board[i][j] != 0)
                displayChosenBox(STARTING_X + (j - 1) * CELLS_WIDTH, STARTING_Y + (i - 1) * CELLS_HEIGHT, CELLS_HEIGHT, CELLS_WIDTH, (char)board[i][j], BLACK, WHITE);
                // Delete the display of current box choosing
            else
            {
                int pX = STARTING_X + (j - 1) * CELLS_WIDTH;
                int pY = STARTING_Y + (i - 1) * CELLS_HEIGHT;
                background_upgrade(pX, pY, background, mode);
                // Get the coordinate to upgrade the background if there's no pokemon here
            }

            j++;
            if (j > gameBoard.col) // Get to the other side of the column
                j = 1;
            if (i == pokemon1.i && j == pokemon1.j) // Can't choose the box already selected unless player choose it the first time
                j++;
            if (j > gameBoard.col) // Get to the other side of the column
                j = 1;
        }

        else if (input == 6 && board[i][j] != 0) // ENTER or SPACEBAR
        {
            count_space_bar++;
            if (count_space_bar % 2 == 1) // Choose first pokemon
            {
                PlaySound(TEXT("Select.wav"), NULL, SND_ASYNC);

                pokemon1.x = STARTING_X + (j - 1) * CELLS_WIDTH; // Coordinate of the chosen pokemon on console window
                pokemon1.y = STARTING_Y + (i - 1) * CELLS_HEIGHT;

                pokemon1.i = i; // Index of the chosen pokemon on the board
                pokemon1.j = j;

                TextColor(AQUA); // Set the color of the seleted box
                displayBoxChar(STARTING_X + (j - 1) * CELLS_WIDTH, STARTING_Y + (i - 1) * CELLS_HEIGHT, CELLS_HEIGHT, CELLS_WIDTH, (char)board[i][j]);
                displayChosenBox(STARTING_X + (j - 1) * CELLS_WIDTH, STARTING_Y + (i - 1) * CELLS_HEIGHT, CELLS_HEIGHT, CELLS_WIDTH, (char)board[i][j], GREEN, WHITE);
                // Display again to perfectly show the current choosing box
            }

            else // Choose second pokemon
            {
                pokemon2.x = STARTING_X + (j - 1) * CELLS_WIDTH; // Coordinate of the chosen pokemon on console window
                pokemon2.y = STARTING_Y + (i - 1) * CELLS_HEIGHT;

                pokemon2.i = i; // index of the chosen pokemon on the board
                pokemon2.j = j;

                TextColor(AQUA); // Set the color of the seleted box
                displayBoxChar(STARTING_X + (j - 1) * CELLS_WIDTH, STARTING_Y + (i - 1) * CELLS_HEIGHT, CELLS_HEIGHT, CELLS_WIDTH, (char)board[i][j]);

                if (checkMatchingAndDisplay(board, pokemon1, pokemon2, score, gameBoard, background, mode)) // kiem tra matching va display
                {
                    if (mode == EASY) // Easy mode
                    {
                        deletePoint(board, pokemon1, pokemon2, mode); // Delete pokemon stored on the board             
                        deleteBox(pokemon1.x, pokemon1.y, CELLS_HEIGHT, CELLS_WIDTH); // Delete the box of 2 matched pokemons
                        deleteBox(pokemon2.x, pokemon2.y, CELLS_HEIGHT, CELLS_WIDTH);
                        background_upgrade(pokemon1.x, pokemon1.y, background, mode); // Upgrade the background for 2 deleted pokemons
                        background_upgrade(pokemon2.x, pokemon2.y, background, mode);
                    }
                    else if (mode == HARD) //Hard mode
                    {
                        deletePoint(board, pokemon1, pokemon2, mode); // Delete pokemon stored on the board   
                        for (int j = 1, temp_x = STARTING_X; j < gameBoard.col + 1; j++, temp_x += CELLS_WIDTH)
                        {
                            // Redraw the row which holds the deleted pokemon in HARD mode
                            if (board[pokemon1.i][j] != 0)
                            {
                                displayBoxChar(temp_x, pokemon1.y, CELLS_HEIGHT, CELLS_WIDTH, board[pokemon1.i][j]);
                            }
                            else
                            {
                                int pX = STARTING_X + (j - 1) * CELLS_WIDTH;
                                int pY = STARTING_Y + (pokemon1.i - 1) * CELLS_HEIGHT;
                                background_upgrade(pX, pY, background, mode);
                                TextColor(WHITE);
                            }
                        }

                        if (pokemon1.i != pokemon2.i)
                        {
                            // Redraw the row which holds the deleted pokemon in HARD mode
                            for (int j = 1, temp_x = STARTING_X; j < gameBoard.col + 1; j++, temp_x += CELLS_WIDTH)
                            {
                                if (board[pokemon2.i][j] != 0)
                                {
                                    displayBoxChar(temp_x, pokemon2.y, CELLS_HEIGHT, CELLS_WIDTH, board[pokemon2.i][j]);
                                }
                                else
                                {
                                    int pX = STARTING_X + (j - 1) * CELLS_WIDTH;
                                    int pY = STARTING_Y + (pokemon2.i - 1) * CELLS_HEIGHT;
                                    background_upgrade(pX, pY, background, mode);
                                }
                            }
                        }
                    }

                    pokemon -= 2;

                    if (pokemon == 0) // Game ends if there's no more pokemon left
                    {
                        updateGameScore(score);
                        int choice;
                        int tempTime = 0;
                        // Saved game statistic
                        if (mode == EASY)
                        {
                            if (list[playerPos]->Easy->gameSavedCheck == true)
                            {
                                tempTime += list[playerPos]->Easy->time;
                            }
                            list[playerPos]->Easy->gameSavedCheck = false;
                        }
                        else
                        {
                            // HARD mode
                            if (list[playerPos]->Hard->gameSavedCheck == true)
                            {
                                tempTime += list[playerPos]->Hard->time;
                            }
                            list[playerPos]->Hard->gameSavedCheck = false;
                        } 
                            

                        if (mode == EASY)
                        {
                            if (list[playerPos]->Easy->bestScore < score) // Update player Highscore
                                list[playerPos]->Easy->bestScore = score;

                            time_ = tempTime + (time(0) - time_); // Get the time through using 1 timestamp to subtract another in second

                            if (list[playerPos]->Easy->bestTime > time_ || list[playerPos]->Easy->bestTime == 0) // Update player Best time
                                list[playerPos]->Easy->bestTime = time_;
                        }
                        else if (mode == HARD)
                        {
                            if (list[playerPos]->Hard->bestScore < score) // Update player Highscore
                                list[playerPos]->Hard->bestScore = score;

                            time_ = tempTime + (time(0) - time_); // Get the time through using 1 timestamp to subtract another in second

                            if (list[playerPos]->Hard->bestTime > time_ || list[playerPos]->Hard->bestTime == 0) // Update player Best time
                                list[playerPos]->Hard->bestTime = time_;
                        }

                        displayWinGame(time_, choice); // Display the Win game box
                        if (choice == 1) // NEW GAME
                        {
                            deleteBoard(board, gameBoard);
                            deleteBackground(background); // Deallocate background
                            goto NEW_GAME;
                        }
                        else // BACK
                            PlaySound(TEXT("Menu.wav"), NULL, SND_ASYNC | SND_LOOP);
                            playloop = false;
                    }

                    Pokemon ignore1, ignore2;

                    while ((!checkContinue(board, ignore1, ignore2, gameBoard)) && pokemon != 0) // Check continue after 2 pokemons have been matched
                    {
                        PlaySound(TEXT("Shuffle.wav"), NULL, SND_ASYNC);
                        shuffleCount--;
                        if (shuffleCount < 0)
                        {
                            // GAME OVER
                            PlaySound(TEXT("Incorrect.wav"), NULL, SND_ASYNC);
                            int choice;
                            displayGameOver(choice); // Display game over box
                            if (choice == 1) // NEW GAME
                            {
                                deleteBoard(board, gameBoard);
                                deleteBackground(background);
                                goto NEW_GAME;
                            }
                            else // BACK
                            {   
                                playloop = false;
                                PlaySound(TEXT("Menu.wav"), NULL, SND_ASYNC | SND_LOOP);
                                break;
                            }
                        }
                        updateShuffles(shuffleCount);
                        deleteBox(87, 21, 9, 31);
                        TextColor(YELLOW);
                        displayBox(87, 21, 9, 31, "Out of moves, let's shufffle!");
                        shuffleBoard(board, gameBoard);
                        TextColor(WHITE);
                        displayAllChar(STARTING_X, STARTING_Y, CELLS_HEIGHT, CELLS_WIDTH, board, gameBoard);
                
                        // To color the missing part
                        TextColor(GREEN * 16 + WHITE);
                        gotoxy(STARTING_X + (j - 1) * CELLS_WIDTH + (CELLS_WIDTH - 1) / 2, STARTING_Y + (i - 1) * CELLS_HEIGHT + CELLS_HEIGHT / 2);
                        cout << (char)board[i][j];

                        // Redraw the board after delete the "Out of moves..."
                        TextColor(WHITE);
                        Sleep(1000);
                        deleteBox(87, 21, 9, 31);
                        displayGameInstruction();
                    }
                }
                else // 2 pokemons selected is wrong
                {
                    PlaySound(TEXT("Incorrect.wav"), NULL, SND_ASYNC);
                    TextColor(RED);
                    displayBoxChar(pokemon1.x, pokemon1.y, CELLS_HEIGHT, CELLS_WIDTH, (char)board[pokemon1.i][pokemon1.j]);
                    displayBoxChar(pokemon2.x, pokemon2.y, CELLS_HEIGHT, CELLS_WIDTH, (char)board[pokemon2.i][pokemon2.j]);
                    Sleep(300);
                    TextColor(WHITE);
                    displayBoxChar(pokemon1.x, pokemon1.y, CELLS_HEIGHT, CELLS_WIDTH, (char)board[pokemon1.i][pokemon1.j]);
                    displayBoxChar(pokemon2.x, pokemon2.y, CELLS_HEIGHT, CELLS_WIDTH, (char)board[pokemon2.i][pokemon2.j]);
                }

                pokemon1.i = pokemon1.j = -1;
            }
        }

        else if (input == 8) // SHUFFLE
        {   
            PlaySound(TEXT("Shuffle.wav"), NULL, SND_ASYNC);
            if (shuffleCount > 0)
            {   
                TextColor(WHITE);
                shuffleCount--;
                count_space_bar = 0; // To reset after 1 pokemon have been pressed
                if (pokemon1.i != -1) // Check if blue box is display or not
                    displayBoxChar(STARTING_X + (pokemon1.j - 1) * CELLS_WIDTH, STARTING_Y + (pokemon1.i - 1) * CELLS_HEIGHT, CELLS_HEIGHT, CELLS_WIDTH, (char)board[i][j]); // To neglect the blue box when press shuffle
                pokemon1.i = pokemon1.j = -1;

                updateShuffles(shuffleCount);
                deleteBox(87, 21, 9, 31);
                TextColor(YELLOW);
                displayBox(87, 21, 9, 31, "Let's shuffle!");
                shuffleBoard(board, gameBoard);
                TextColor(WHITE);
                deleteBox(STARTING_X + 1 + (j - 1) * CELLS_WIDTH, STARTING_Y + 1 + (i - 1) * CELLS_HEIGHT, CELLS_HEIGHT - 2, CELLS_WIDTH - 2); // Delete the display of chosen box
                displayAllChar(STARTING_X, STARTING_Y, CELLS_HEIGHT, CELLS_WIDTH, board, gameBoard);
                
                // Redraw the board after delete the "Let's shuffle!"
                TextColor(WHITE);
                Sleep(1000);
                deleteBox(87, 21, 9, 31);
                displayGameInstruction();
            }
            else // No more shuffles left
            {
                PlaySound(TEXT("Incorrect.wav"), NULL, SND_ASYNC);
                displayRunOutOfShuffle();
                Sleep(500);
                deleteBox(87, 21, 9, 31);
                displayGameInstruction();
            }
        }

        else if (input == 7) //HINT
        {
            Pokemon temp1, temp2;

            checkContinue(board, temp1, temp2, gameBoard); // Get the 2 pokemons that have a match
            temp1.x = STARTING_X + (temp1.j - 1) * CELLS_WIDTH;
            temp1.y = STARTING_Y + (temp1.i - 1) * CELLS_HEIGHT;
            temp2.x = STARTING_X + (temp2.j - 1) * CELLS_WIDTH;
            temp2.y = STARTING_Y + (temp2.i - 1) * CELLS_HEIGHT;

            TextColor(LIGHT_GREEN); // Display 2 pokemons in bright color to easily spot
            displayBoxChar(temp1.x, temp1.y, CELLS_HEIGHT, CELLS_WIDTH, board[temp1.i][temp1.j]);
            displayBoxChar(temp2.x, temp2.y, CELLS_HEIGHT, CELLS_WIDTH, board[temp2.i][temp2.j]);
            Sleep(500);
            TextColor(WHITE);
            displayBoxChar(temp1.x, temp1.y, CELLS_HEIGHT, CELLS_WIDTH, board[temp1.i][temp1.j]);
            displayBoxChar(temp2.x, temp2.y, CELLS_HEIGHT, CELLS_WIDTH, board[temp2.i][temp2.j]);

            if ((pokemon1.i == temp1.i && pokemon1.j == temp1.j) || (pokemon1.i == temp2.i && pokemon1.j == temp2.j))
            {
                // If a selected pokemon is the same with the 2 pokemon returned from checkContinue
                // Redraw the selected Box
                TextColor(AQUA);
                displayBoxChar(pokemon1.x, pokemon1.y, CELLS_HEIGHT, CELLS_WIDTH, char(board[pokemon1.i][pokemon1.j]));
            }
            score -= 7;
        }
        else if (input == 1) // ESC_KEY
        {
            int choice;
            displayConfirmQuit(choice); // Display confirm quit box
            if (choice == 1) // GAME SAVED YES
            {
                if (mode == EASY)
                {
                    // Saved game essentials info
                    copyBoardEasy(list, playerPos, board, gameBoard);
                    list[playerPos]->Easy->score = score;
                    list[playerPos]->Easy->pokemon = pokemon;
                    list[playerPos]->Easy->time += (time(0) - time_);
                    list[playerPos]->Easy->shuffleCount = shuffleCount;
                    list[playerPos]->Easy->gameSavedCheck = 1;
                }

                else if (mode == HARD)
                {
                    // Saved game essentials info
                    copyBoardHard(list, playerPos, board, gameBoard);
                    list[playerPos]->Hard->score = score;
                    list[playerPos]->Hard->pokemon = pokemon;
                    list[playerPos]->Hard->time += (time(0) - time_);
                    list[playerPos]->Hard->shuffleCount = shuffleCount;
                    list[playerPos]->Hard->gameSavedCheck = 1;
                }
            }
            else // GAME SAVED NO
            {
                if (mode == EASY)
                {
                    list[playerPos]->Easy->gameSavedCheck = false;
                }
                else 
                {
                    list[playerPos]->Hard->gameSavedCheck = false;
                }
            }
            PlaySound(TEXT("Menu.wav"), NULL, SND_ASYNC | SND_LOOP);
            playloop = false;
        }
    }
}

void GameplayMemory(int**& board, Board& gameBoard, vector <Player*> list, int playerPos){
NEW_GAME:
    // Initiate the gameBoard statistics
    gameBoard.col = 8;
    gameBoard.row = 5; 
    gameBoard.width = gameBoard.col * CELLS_WIDTH;
    gameBoard.height = gameBoard.row * CELLS_HEIGHT;

    int mode = MEMORY;
    int pokemon;
    int count_space_bar, score;
    int shuffleCount = 5;
    int i = 1, j = 1; // Current selected cell
    
    if (list[playerPos]->Memory->gameSavedCheck == 1)
    {
        int choice;
        displayContinueGame(choice);
        if (choice == 1) // Player chose YES
        {
            // Copy all of saved game information to current game
            createBoard(board, gameBoard);
            copyBoard(board, list[playerPos]->Memory->board, gameBoard);
            score = list[playerPos]->Memory->score;
            pokemon = list[playerPos]->Memory->pokemon;
            shuffleCount = list[playerPos]->Memory->shuffleCount;
        }
        else // Player chose NO
        {   
            // Delete the saved game and create a new game
            list[playerPos]->Memory->gameSavedCheck = 0;
            goto NEW_GAME;
        }
    }
    else  // No saved game is found
    {
        Pokemon ignore1, ignore2;
        createBoard(board, gameBoard);
        createPoint(board, gameBoard);
        while (!checkContinue(board, ignore1, ignore2, gameBoard))
        {
            shuffleBoard(board, gameBoard);
            // Find a board that's playable for the player
        }
        pokemon = gameBoard.col * gameBoard.row;
        count_space_bar = 0;
        score = 0;
    }

    if (!readyInstructionMemoryMode()) // Check if player is ready or not
    { // BACK
        
        return;
    }
    else // READY
    {
        system("cls");
    }
    bool playloop = true;

    string* background = createBackground(); 
    getBackground("images/background_3.txt", background);
    // Load the background

    system("cls");
    displayPlayerInfo(list, playerPos); // Display the player info: High score and Best time for each mode
    displayGameStatistic(); // Display a box for player current score and shuffle left of the playing game
    displayGameInstruction(); // Display small instruction for player to help player with the game
    updateShuffles(shuffleCount); // Update player current shuffle count
    displayGameBox(STARTING_X, STARTING_Y, CELLS_HEIGHT, CELLS_WIDTH, board, gameBoard, background, mode);
    
    Sleep(5000); // <------------------ TIME TO WATCH THE BOARD

    displayEraseAllChar(STARTING_X, STARTING_Y, CELLS_HEIGHT, CELLS_WIDTH, board, gameBoard);
    Pokemon pokemon1, pokemon2;
    pokemon1.x = -1; pokemon1.y = -1; pokemon1.i = -1; pokemon1.j = -1;
    pokemon2.x = -1; pokemon2.y = -1; pokemon2.i = -1; pokemon2.j = -1;

    int time_;
    time_ = time(0);
    // Store current timestamp starting to play in seconds
    while (playloop)
    {
        displayChosenBox(STARTING_X + (j - 1) * CELLS_WIDTH, STARTING_Y + (i - 1) * CELLS_HEIGHT, CELLS_HEIGHT, CELLS_WIDTH, ' ', GREEN, WHITE);
        // Display current box choosing
        if (score < 0) score = 0;
        updateGameScore(score); // Update player current score
        int input = getConsoleInput(); // Get player input

        if (input == 2) // KEY UP
        {
            TextColor(WHITE);
            if (board[i][j] != 0)
                displayChosenBox(STARTING_X + (j - 1) * CELLS_WIDTH, STARTING_Y + (i - 1) * CELLS_HEIGHT, CELLS_HEIGHT, CELLS_WIDTH, ' ', BLACK, WHITE);
                // Delete the display of current box choosing
            else
            {
                int pX = STARTING_X + (j - 1) * CELLS_WIDTH;
                int pY = STARTING_Y + (i - 1) * CELLS_HEIGHT;
                background_upgrade(pX, pY, background, mode);
                // Get the coordinate to upgrade the background if there's no pokemon here
            }
            i--;
            if (i < 1) // Get to the other side of the row
                i = gameBoard.row;
            if (i == pokemon1.i && j == pokemon1.j) // Can't choose the box already selected unless player choose it the first time
                i--;
            if (i < 1) // Get to the other side of the row
                i = gameBoard.row;
        }

        else if (input == 5) // KEY DOWN
        {
            TextColor(WHITE);
            if (board[i][j] != 0)
                displayChosenBox(STARTING_X + (j - 1) * CELLS_WIDTH, STARTING_Y + (i - 1) * CELLS_HEIGHT, CELLS_HEIGHT, CELLS_WIDTH, ' ', BLACK, WHITE);
                // Delete the display of current box choosing
            else
            {
                int pX = STARTING_X + (j - 1) * CELLS_WIDTH;
                int pY = STARTING_Y + (i - 1) * CELLS_HEIGHT;
                background_upgrade(pX, pY, background, mode);
                // Get the coordinate to upgrade the background if there's no pokemon here
            }

            i++;
            if (i > gameBoard.row) // Get to the other side of the row
                i = 1;
            if (i == pokemon1.i && j == pokemon1.j) // Can't choose the box already selected unless player choose it the first time
                i++;
            if (i > gameBoard.row) // Get to the other side of the row
                i = 1;
        }

        else if (input == 3) // KEY LEFT
        {
            TextColor(WHITE);
            if (board[i][j] != 0)
                displayChosenBox(STARTING_X + (j - 1) * CELLS_WIDTH, STARTING_Y + (i - 1) * CELLS_HEIGHT, CELLS_HEIGHT, CELLS_WIDTH, ' ', BLACK, WHITE);
                // Delete the display of current box choosing
            else
            {
                int pX = STARTING_X + (j - 1) * CELLS_WIDTH;
                int pY = STARTING_Y + (i - 1) * CELLS_HEIGHT;
                background_upgrade(pX, pY, background, mode);
                // Get the coordinate to upgrade the background if there's no pokemon here
            }

            j--;
            if (j < 1) // Get to the other side of the column
                j = gameBoard.col;
            if (i == pokemon1.i && j == pokemon1.j) // Can't choose the box already selected unless player choose it the first time
                j--;
            if (j < 1) // Get to the other side of the column
                j = gameBoard.col;
        }

        else if (input == 4) // KEY RIGHT
        {
            TextColor(WHITE);
            if (board[i][j] != 0)
                displayChosenBox(STARTING_X + (j - 1) * CELLS_WIDTH, STARTING_Y + (i - 1) * CELLS_HEIGHT, CELLS_HEIGHT, CELLS_WIDTH, ' ', BLACK, WHITE);
                // Delete the display of current box choosing
            else
            {
                int pX = STARTING_X + (j - 1) * CELLS_WIDTH;
                int pY = STARTING_Y + (i - 1) * CELLS_HEIGHT;
                background_upgrade(pX, pY, background, mode);
                // Get the coordinate to upgrade the background if there's no pokemon here
            }

            j++;
            if (j > gameBoard.col) // Get to the other side of the column
                j = 1;
            if (i == pokemon1.i && j == pokemon1.j) // Can't choose the box already selected unless player choose it the first time
                j++;
            if (j > gameBoard.col) // Get to the other side of the column
                j = 1;
        }

        else if (input == 6 && board[i][j] != 0) // ENTER or SPACEBAR
        {
            count_space_bar++;
            if (count_space_bar % 2 == 1) // Choose first pokemon
            {
                PlaySound(TEXT("Select.wav"), NULL, SND_ASYNC);

                pokemon1.x = STARTING_X + (j - 1) * CELLS_WIDTH; // Coordinate of the chosen pokemon on console window
                pokemon1.y = STARTING_Y + (i - 1) * CELLS_HEIGHT;

                pokemon1.i = i; // Index of the chosen pokemon on the board
                pokemon1.j = j;

                TextColor(AQUA); // Set the color of the seleted box
                displayBoxChar(STARTING_X + (j - 1) * CELLS_WIDTH, STARTING_Y + (i - 1) * CELLS_HEIGHT, CELLS_HEIGHT, CELLS_WIDTH, ' ');
                displayChosenBox(STARTING_X + (j - 1) * CELLS_WIDTH, STARTING_Y + (i - 1) * CELLS_HEIGHT, CELLS_HEIGHT, CELLS_WIDTH, ' ', GREEN, WHITE);
                // Display again to perfectly show the current choosing box
            }

            else // Choose second pokemon
            {
                pokemon2.x = STARTING_X + (j - 1) * CELLS_WIDTH; // Coordinate of the chosen pokemon on console window
                pokemon2.y = STARTING_Y + (i - 1) * CELLS_HEIGHT;

                pokemon2.i = i; // Index of the chosen pokemon on the board
                pokemon2.j = j;

                TextColor(AQUA); // Set the color of the seleted box
                displayBoxChar(STARTING_X + (j - 1) * CELLS_WIDTH, STARTING_Y + (i - 1) * CELLS_HEIGHT, CELLS_HEIGHT, CELLS_WIDTH, ' ');

                if (checkMatchingAndDisplay(board, pokemon1, pokemon2, score, gameBoard, background, mode)) // kiem tra matching va display
                {
                    deletePoint(board, pokemon1, pokemon2, 0); // Delete pokemon stored on the board                         
                    deleteBox(pokemon1.x, pokemon1.y, CELLS_HEIGHT, CELLS_WIDTH); // Delete the box of 2 matched pokemons
                    deleteBox(pokemon2.x, pokemon2.y, CELLS_HEIGHT, CELLS_WIDTH);
                    background_upgrade(pokemon1.x, pokemon1.y, background, mode); // Upgrade the background for 2 deleted pokemons
                    background_upgrade(pokemon2.x, pokemon2.y, background, mode);

                    displayAllChar(STARTING_X, STARTING_Y, CELLS_HEIGHT, CELLS_WIDTH, board, gameBoard);
                
                    updateGameScore(score);

                    Sleep(4000); // <------------ Time for pokemons to appear when 2 is matched
                    displayEraseAllChar(STARTING_X, STARTING_Y, CELLS_HEIGHT, CELLS_WIDTH, board, gameBoard);

                    pokemon -= 2;

                    if (pokemon == 0) // Game ends if there's no more pokemon left
                    {
                        updateGameScore(score);
                        int choice;
                        int tempTime = 0;
                        // Saved game statistic
                        if (list[playerPos]->Memory->gameSavedCheck == true)
                        {
                            tempTime += list[playerPos]->Memory->time;
                        }
                        list[playerPos]->Memory->gameSavedCheck = false;

                        if (list[playerPos]->Memory->bestScore < score) // Update player Highscore
                            list[playerPos]->Memory->bestScore = score;

                        time_ = tempTime + (time(0) - time_); // Get the time through using 1 timestamp to subtract another in second

                        if (list[playerPos]->Memory->bestTime > time_ || list[playerPos]->Memory->bestTime == 0) // Update player Best time
                            list[playerPos]->Memory->bestTime = time_;

                        displayWinGame(time_, choice); // Display the Win game box
                        if (choice == 1) // NEW GAME
                        {
                            deleteBoard(board, gameBoard);
                            deleteBackground(background); // Deallocate background
                            goto NEW_GAME;
                        }
                        else // BACK
                            PlaySound(TEXT("Menu.wav"), NULL, SND_ASYNC | SND_LOOP); // Play sound when back to menu
                            playloop = false;
                    }

                    Pokemon ignore1, ignore2;

                    while ((!checkContinue(board, ignore1, ignore2, gameBoard)) && pokemon != 0) // Check continue after 2 pokemons have been matched
                    {
                        PlaySound(TEXT("Shuffle.wav"), NULL, SND_ASYNC);
                        shuffleCount--;
                        if (shuffleCount < 0)
                        {
                            // GAME OVER
                            PlaySound(TEXT("Incorrect.wav"), NULL, SND_ASYNC);
                            int choice;
                            displayGameOver(choice); // Display game over box
                            if (choice == 1) // NEW GAME
                            {
                                deleteBoard(board, gameBoard);
                                deleteBackground(background);
                                goto NEW_GAME;
                            }
                            else // BACK
                            {   
                                playloop = false;
                                PlaySound(TEXT("Menu.wav"), NULL, SND_ASYNC | SND_LOOP);
                                break;
                            }
                        }
                        updateShuffles(shuffleCount);
                        deleteBox(87, 21, 9, 31);
                        TextColor(YELLOW);
                        displayBox(87, 21, 9, 31, "Out of moves, let's shufffle!");
                        shuffleBoard(board, gameBoard);
                        TextColor(WHITE);
                        displayAllChar(STARTING_X, STARTING_Y, CELLS_HEIGHT, CELLS_WIDTH, board, gameBoard);
                
                        // To color the missing part
                        TextColor(GREEN * 16 + WHITE);
                        gotoxy(STARTING_X + (j - 1) * CELLS_WIDTH + (CELLS_WIDTH - 1) / 2, STARTING_Y + (i - 1) * CELLS_HEIGHT + CELLS_HEIGHT / 2);
                        cout << (char)board[i][j];

                        // Redraw the board after delete the "Out of moves..."
                        TextColor(WHITE);
                        Sleep(5000); // <------------ Time for pokemons to appear before being dissapeared
                        displayEraseAllChar(STARTING_X, STARTING_Y, CELLS_HEIGHT, CELLS_WIDTH, board, gameBoard);

                        deleteBox(87, 21, 9, 31);
                        displayGameInstruction();
                    }
                }
                else // 2 pokemons selected is wrong
                {
                    PlaySound(TEXT("Incorrect.wav"), NULL, SND_ASYNC);
                    TextColor(RED);
                    displayBoxChar(pokemon1.x, pokemon1.y, CELLS_HEIGHT, CELLS_WIDTH, ' ');
                    displayBoxChar(pokemon2.x, pokemon2.y, CELLS_HEIGHT, CELLS_WIDTH, ' ');
                    Sleep(300);
                    TextColor(WHITE);
                    displayBoxChar(pokemon1.x, pokemon1.y, CELLS_HEIGHT, CELLS_WIDTH, ' ');
                    displayBoxChar(pokemon2.x, pokemon2.y, CELLS_HEIGHT, CELLS_WIDTH, ' ');
                }

                pokemon1.i = pokemon1.j = -1;
            }
        }

        else if (input == 8) // SHUFFLE
        {   
            PlaySound(TEXT("Shuffle.wav"), NULL, SND_ASYNC);
            if (shuffleCount > 0)
            {   
                TextColor(WHITE);
                shuffleCount--;
                count_space_bar = 0; // To reset after 1 pokemon have been pressed
                if (pokemon1.i != -1) // Check if blue box is display or not
                    displayBoxChar(STARTING_X + (pokemon1.j - 1) * CELLS_WIDTH, STARTING_Y + (pokemon1.i - 1) * CELLS_HEIGHT, CELLS_HEIGHT, CELLS_WIDTH, (char)board[i][j]); // To neglect the blue box when press shuffle
                pokemon1.i = pokemon1.j = -1;
                
                updateShuffles(shuffleCount);
                deleteBox(87, 21, 9, 31);
                TextColor(YELLOW);
                displayBox(87, 21, 9, 31, "Let's shufffle!");
                shuffleBoard(board, gameBoard);
                TextColor(WHITE);
                deleteBox(STARTING_X + 1 + (j - 1) * CELLS_WIDTH, STARTING_Y + 1 + (i - 1) * CELLS_HEIGHT, CELLS_HEIGHT - 2, CELLS_WIDTH - 2); // Delete the display of chosen box
                displayAllChar(STARTING_X, STARTING_Y, CELLS_HEIGHT, CELLS_WIDTH, board, gameBoard);
                
                TextColor(WHITE);
                Sleep(5000); // <------------ Time for pokemons to appear before being dissapeared
                displayEraseAllChar(STARTING_X, STARTING_Y, CELLS_HEIGHT, CELLS_WIDTH, board, gameBoard);

                // Redraw the board after delete the "Let's shuffle!"
                deleteBox(87, 21, 9, 31);
                displayGameInstruction();
            }
            else
            {
                // No more shuffles left
                PlaySound(TEXT("Incorrect.wav"), NULL, SND_ASYNC);
                displayRunOutOfShuffle();
                Sleep(500);
                deleteBox(87, 21, 9, 31);
                displayGameInstruction();
            }
        }

        else if (input == 7) // HINT
        {
            // Show all pokemons for an amount of seconds
            TextColor(WHITE);
            displayAllChar(STARTING_X, STARTING_Y, CELLS_HEIGHT, CELLS_WIDTH, board, gameBoard);
                
            // To color the missing part
            TextColor(GREEN * 16 + WHITE);
            gotoxy(STARTING_X + (j - 1) * CELLS_WIDTH + (CELLS_WIDTH - 1) / 2, STARTING_Y + (i - 1) * CELLS_HEIGHT + CELLS_HEIGHT / 2);
            cout << (char)board[i][j];

            TextColor(WHITE);
            Sleep(5000); // <------------ Time for pokemons to appear before being dissapeared
            displayEraseAllChar(STARTING_X, STARTING_Y, CELLS_HEIGHT, CELLS_WIDTH, board, gameBoard);
            score -= 7;
        }

        else if (input == 1) // ESC KEY
        {
            int choice;
            displayConfirmQuit(choice); // Display confirm quit box
            if (choice == 1) // GAME SAVED YES
            {
                // Saved game essentials info
                copyBoardMemory(list, playerPos, board, gameBoard);
                list[playerPos]->Memory->score = score;
                list[playerPos]->Memory->pokemon = pokemon;
                list[playerPos]->Memory->time += (time(0) - time_);
                list[playerPos]->Memory->shuffleCount = shuffleCount;
                list[playerPos]->Memory->gameSavedCheck = 1;
            }
            else // GAME SAVED NO
            {
                list[playerPos]->Memory->gameSavedCheck = false;
            }
            PlaySound(TEXT("Menu.wav"), NULL, SND_ASYNC | SND_LOOP);
            playloop = false;
        }
    }
}

void deleteBoard(int**& board, Board gameBoard) 
{
    // Deallocate the board
    for (int i = 0; i < gameBoard.row + 2; i++)
    {
        delete[] board[i];
    }
    delete[] board;
    board = NULL;
}

void deleteBackground(string* background)
{
    // Deallocate the background
    delete[] background;
    background = NULL;
}