#include "Display.h"

void displayBox(int x, int y, int boxHeight, int boxWidth, string s) 
{
	// Input the corner up-left coordinate of the box and box's size
	char c;
	c = 205;
	for (int i = 0; i < boxWidth; i++) 
	{
		gotoxy(x + i, y);
		cout << c;
		gotoxy(x + i, y + boxHeight - 1);
		cout << c;
	}
	// Draw top edge and bottom edge

	c = 186;
	for (int i = 0; i < boxHeight; i++)
	{
		gotoxy(x + boxWidth - 1, y + i);
		cout << c;
		gotoxy(x, y + i);
		cout << c;
	}
	// Draw left edge and right edge

	c = 188;
	gotoxy(x + boxWidth - 1, y + boxHeight - 1);
	cout << c;
	// Draw bottom-right corner

	c = 201;
	gotoxy(x, y);
	cout << c;
	// Draw top-left corner

	c = 187;
	gotoxy(x + boxWidth - 1, y);
	cout << c;
	// Draw top-right corner

	c = 200;
	gotoxy(x, y + boxHeight - 1);
	cout << c;
	// Draw bottom-left corner

	gotoxy(x + (boxWidth - s.length()) / 2, y + boxHeight / 2);
	cout << s;
	// Input the string s into the box with the formula to center the string
}

void displayChosenBox(int x, int y, int boxHeight, int boxWidth, char s, int background, int text)
{
	// Set the display for the current box user is on
	TextColor(background * 16 + text);
	// Set the background and text color, here: normally GREEN background and WHITE text
	char c = 32;

	for (int i = 1; i < boxHeight - 1; i++){
		for (int j = 1; j < boxWidth - 1; j++){
			gotoxy(x + j, y + i);
			cout << c;
		}
	}

	gotoxy(x + (boxWidth - 1) / 2, y + boxHeight / 2);
	cout << s;
	// Get the char to the center of the box
}

void displayLogo(int x, int y)
{
	// Just the logo of the game
	gotoxy(x, y);
	cout << R"(
			  ________  ___  ___  __    ________  ________  ___  ___  ___  ___     
			 |\   __  \|\  \|\  \|\  \ |\   __  \|\   ____\|\  \|\  \|\  \|\  \    
			 \ \  \|\  \ \  \ \  \/  /|\ \  \|\  \ \  \___|\ \  \\\  \ \  \\\  \   
			  \ \   ____\ \  \ \   ___  \ \   __  \ \  \    \ \   __  \ \  \\\  \  
			   \ \  \___|\ \  \ \  \\ \  \ \  \ \  \ \  \____\ \  \ \  \ \  \\\  \ 
			    \ \__\    \ \__\ \__\\ \__\ \__\ \__\ \_______\ \__\ \__\ \_______\
			     \|__|     \|__|\|__| \|__|\|__|\|__|\|_______|\|__|\|__|\|_______|

	)";
}

void displayMenuScreen()
{
	// Display the logo, but with colour
	TextColor(YELLOW);
	displayLogo(18, 1);
	TextColor(WHITE);
}

void displayGameBox(int x, int y, int boxHeight, int boxWidth, int** board, Board gameBoard, string* background, int mode) // print up to down, then left to right
{
	// Display all the character in board if found, if not just show the background
	for (int w = 0, j = 1; j < gameBoard.col + 1; w += CELLS_WIDTH, j++)
	{
		for (int l = 0, i = 1; i < gameBoard.row + 1; l += CELLS_HEIGHT, i++)
		{
			if (board[i][j] != 0)
				displayBoxChar(x + w, y + l, CELLS_HEIGHT, CELLS_WIDTH, (char)board[i][j]);
			else{
				background_upgrade(x + w, y + l, background, mode);
				// Mode here is for which mode you are playing
				// For each mode, there's a diffrent background
			}
		}
	}
}

void displayAllChar(int x, int y, int boxHeight, int boxWidth, int** board, Board gameBoard)
{
	// Display just the char of the box, to reduce the time console has to draw
	for (int w = 0, j = 1; j < gameBoard.col + 1; w += CELLS_WIDTH, j++)
	{
		for (int l = 0, i = 1; i < gameBoard.row + 1; l += CELLS_HEIGHT, i++)
		{
			if (board[i][j] != 0)
			{
				gotoxy(x + w + (boxWidth - 1) / 2, y + l + boxHeight / 2);
				cout << (char)board[i][j];
			}
		}
	}
}

void displayEraseAllChar(int x, int y, int boxHeight, int boxWidth, int** board, Board gameBoard)
{
	// Function used for the MEMORY mode, to make all character dissapear/
	for (int w = 0, j = 1; j < gameBoard.col + 1; w += CELLS_WIDTH, j++)
	{
		for (int l = 0, i = 1; i < gameBoard.row + 1; l += CELLS_HEIGHT, i++)
		{
			if (board[i][j] != 0)
			{
				gotoxy(x + w + (boxWidth - 1) / 2, y + l + boxHeight / 2);
				cout << ' ';
			}
		}
	}
}

void displayPokeball(int x, int y, int ball_color)
{
	// Displaying the Pokeball at (x, y)
	TextColor(ball_color);
	gotoxy(x, y);
	gotoxy(x + 7, y); cout << "///////////* "; gotoxy(x, ++y);
	gotoxy(x + 4, y);  cout << "/////////////////* "; gotoxy(x, ++y);
	gotoxy(x + 1, y); cout << " /////////////////////* "; gotoxy(x, ++y);
	cout << " //////////     ////////* "; gotoxy(x, ++y);
	cout << " ///////"; TextColor(7); cout << "   @@@@@   "; TextColor(ball_color); cout << "/////*"; gotoxy(x, ++y);
	TextColor(7);
	cout << "          @@@@@@@        "; gotoxy(x, ++y);
	cout << " @@@@@@@   @@@@@   @@@@@&"; gotoxy(x, ++y);
	cout << " @@@@@@@@@       @@@@@@@&"; gotoxy(x, ++y);
	cout << "  @@@@@@@@@@@@@@@@@@@@@&"; gotoxy(x, ++y);
	cout << "    @@@@@@@@@@@@@@@@@& "; gotoxy(x, ++y);
	cout << "       @@@@@@@@@@@&  "; gotoxy(x, ++y);
}

void background_upgrade(int pX, int pY, string* background, int mode)
{
	// Function used to draw the background once a cell disapear or when loading games
	if (mode == EASY)
	{
		for (int i = 0; i < CELLS_WIDTH; i++)
		{
			for (int j = 0; j < CELLS_HEIGHT; j++)
			{	
				int y = pY + j - STARTING_Y;
				int x = pX + i - STARTING_X;
				// (pX, pY) is the coordinate on the console
				// (x, y) is the coordinate on the background matrix
				// The background matrix start at the (STARTING_X, STARTING_Y) aka (4, 3)
				// Whereas the console start at (0, 0) 
				gotoxy(pX + i, pY + j);
				int color;
				if (background[y][x] == '@'){
					color = YELLOW;
				}
				else if (background[y][x] == '#'){
					color = LIGHT_RED;
				}
				else{
					color = WHITE;
				}
				// Color specific part of the background
				TextColor(color);
				cout << background[y][x];
			}
		}
		TextColor(WHITE);
	}
	else if (mode == HARD)
	{
		for (int i = 0; i < CELLS_WIDTH; i++)
		{
			for (int j = 0; j < CELLS_HEIGHT; j++)
			{	
				int y = pY + j - STARTING_Y;
				int x = pX + i - STARTING_X;
				// (pX, pY) is the coordinate on the console
				// (x, y) is the coordinate on the background matrix
				// The background matrix start at the (STARTING_X, STARTING_Y) aka (4, 3)
				// Whereas the console start at (0, 0) 
				gotoxy(pX + i, pY + j);
				int color;
				if (background[y][x] == 'O'){
					color = YELLOW;
				}
				else if (background[y][x] == 'x' || background[y][x] == 'd' || background[y][x] == 'c'){
					color = LIGHT_RED;
				}
				else{
					color = GRAY;
				}
				// Color specific part of the background
				TextColor(color);
				cout << background[y][x];
			}
		}
		TextColor(WHITE);
	}
	else if (mode == MEMORY)
	{
		for (int i = 0; i < CELLS_WIDTH; i++)
		{
			for (int j = 0; j < CELLS_HEIGHT; j++)
			{	
				int y = pY + j - STARTING_Y;
				int x = pX + i - STARTING_X;
				// (pX, pY) is the coordinate on the console
				// (x, y) is the coordinate on the background matrix
				// The background matrix start at the (STARTING_X, STARTING_Y) aka (4, 3)
				// Whereas the console start at (0, 0) 
				gotoxy(pX + i, pY + j);
				int color;
				if (background[y][x] == '@'){
					color = GRAY;
				}
				else if (background[y][x] == 'O'){
					color = GREEN;
				}
				else{
					color = BRIGHT_WHITE;
				}
				// Color specific part of the background
				TextColor(color);
				cout << background[y][x];
			}
		}
		TextColor(WHITE);
	}
}

void background_upgrade_line(Pokemon p1, Pokemon p2, string* background, int mode)
{
	if (p1.x > p2.x || p1.y > p2.y)
		swap(p1, p2); //p1 < p2
	if (p1.x < STARTING_X)
	{
		if (p2.x < STARTING_X) return; 
		p1.x += CELLS_WIDTH;
	}
	else if (p2.x >= STARTING_X + 8 * CELLS_WIDTH)
	{
		if (p1.x >= STARTING_X + 8 * CELLS_WIDTH) return;
		p2.x -= CELLS_WIDTH - 2; // -2 to start from rightmost
	}
	else if (p1.y < STARTING_Y)
	{
		if (p2.y < STARTING_Y) return;
		p1.y += CELLS_HEIGHT;
	}
	else if (p2.y >= STARTING_Y + 5 * CELLS_HEIGHT)
	{
		if (p1.y >= STARTING_Y + 5 * CELLS_HEIGHT) return;
		p2.y -= CELLS_HEIGHT - 2; // -2 to start from downmost
	}
	int boxWidth = p2.x - p1.x + 1;
	int boxHeight = p2.y - p1.y + 1;
	if (mode == EASY)
	{
		for (int i = 0; i < boxWidth; i++)
		{
			for (int j = 0; j < boxHeight; j++)
			{	
				// x, y to get the coord of background
				int x = p1.x + i + 1; // + 1 = - STARTING_X + CELLS_WIDTH / 2
				int y = p1.y + j - 1; // - 1 = - STARTING_Y + CELLS_HEIGHT / 2
				gotoxy(p1.x + i + CELLS_WIDTH / 2, p1.y + j + CELLS_HEIGHT / 2);
				int color;
				if (background[y][x] == '@'){
					color = YELLOW;
				}
				else if (background[y][x] == '#'){
					color = LIGHT_RED;
				}
				else{
					color = WHITE;
				}
				// Color specific part of the background
				TextColor(color);
				cout << background[y][x];
			}
		}
	}
	else if (mode == HARD)
	{
		for (int i = 0; i < boxWidth; i++)
		{
			for (int j = 0; j < boxHeight; j++)
			{	
				// x, y to get the coord of background
				int x = p1.x + i + 1; // + 1 = - STARTING_X + CELLS_WIDTH / 2
				int y = p1.y + j - 1; // - 1 = - STARTING_Y + CELLS_HEIGHT / 2
				gotoxy(p1.x + i + CELLS_WIDTH / 2, p1.y + j + CELLS_HEIGHT / 2);
				int color;
				if (background[y][x] == 'O'){
					color = YELLOW;
				}
				else if (background[y][x] == 'x' || background[y][x] == 'd' || background[y][x] == 'c'){
					color = LIGHT_RED;
				}
				else{
					color = GRAY;
				}
				// Color specific part of the background
				TextColor(color);
				cout << background[y][x];
			}
		}
	}
	else if (mode == MEMORY)
	{
		for (int i = 0; i < boxWidth; i++)
		{
			for (int j = 0; j < boxHeight; j++)
			{	
				// x, y to get the coord of background
				int x = p1.x + i + 1; // + 1 = - STARTING_X + CELLS_WIDTH / 2
				int y = p1.y + j - 1; // - 1 = - STARTING_Y + CELLS_HEIGHT / 2
				gotoxy(p1.x + i + CELLS_WIDTH / 2, p1.y + j + CELLS_HEIGHT / 2);
				int color;
				if (background[y][x] == '@'){
					color = GRAY;
				}
				else if (background[y][x] == 'O'){
					color = GREEN;
				}
				else{
					color = BRIGHT_WHITE;
				}
				// Color specific part of the background
				TextColor(color);
				cout << background[y][x];
			}
		}
	}
	TextColor(WHITE);
}

void deleteBox(int x, int y, int boxHeight, int boxWidth)
{	
	// Delete everything inside with the box size, starting from (x, y)
	// Without using the background, background is BLACK
	gotoxy(x, y);
	for (int i = 0; i < boxHeight; i++)
	{
		for (int j = 0; j < boxWidth; j++)
		{
			cout << " ";
		}
		gotoxy(x, ++y);
	}
}

void displayBoxChar(int x, int y, int boxHeight, int boxWidth, char s)
{
	// Similar to function displayBox at line 3, but with a char instead of a string
	char c;
	c = 205;
	for (int i = 0; i < boxWidth; i++)
	{
		gotoxy(x + i, y);
		cout << c;
		gotoxy(x + i, y + boxHeight - 1);
		cout << c;
	}


	c = 186;
	for (int i = 0; i < boxHeight; i++)
	{
		gotoxy(x + boxWidth - 1, y + i);
		cout << c;
		gotoxy(x, y + i);
		cout << c;
	}

	c = 188;
	gotoxy(x + boxWidth - 1, y + boxHeight - 1);
	cout << c;

	c = 201;
	gotoxy(x, y);
	cout << c;

	c = 187;
	gotoxy(x + boxWidth - 1, y);
	cout << c;

	c = 200;
	gotoxy(x, y + boxHeight - 1);
	cout << c;

	for (int i = 1; i < boxHeight - 1; i++)
	{
		for (int j = 1; j < boxWidth - 1; j++)
		{
			gotoxy(x + j, y + i);
			cout << " ";
		}
	}

	if ((int)s != 0)
	{
		gotoxy(x + (boxWidth - 1) / 2, y + boxHeight / 2);
		cout << s;
	}
}

void displayPlayerInfo(vector <Player*> list, int playerPos)
{
	// Display all the player info box at the upper right side
	// when player are playing the game
	// This will be in the game screen
	// This normally just be called once when the game is call
	TextColor(AQUA);
	displayBox(87, 0, 17, 31, "");
	gotoxy(97, 2);
	TextColor(YELLOW);
	cout << "PLAYER INFO";
	gotoxy(89, 4);
	TextColor(WHITE);
	cout << "NAME: ";
	cout << list[playerPos]->userName;

	gotoxy(89, 6);
	cout << "HIGH SCORE";
	gotoxy(89, 7);
	cout << "- EASY MODE: ";
	cout << list[playerPos]->Easy->bestScore;
	gotoxy(89, 8);
	cout << "- HARD MODE: ";
	cout << list[playerPos]->Hard->bestScore;
	gotoxy(89, 9);
	cout << "- MEMORY MODE: ";
	cout << list[playerPos]->Memory->bestScore;

	gotoxy(89, 11);
	cout << "BEST TIME: ";
	gotoxy(89, 12);
	cout << "- EASY MODE: ";
	cout << list[playerPos]->Easy->bestTime;
	gotoxy(89, 13);
	cout << "- HARD MODE: ";
	cout << list[playerPos]->Hard->bestTime;
	gotoxy(89, 14);
	cout << "- MEMORY MODE: ";
	cout << list[playerPos]->Memory->bestTime;
}

void displayGameStatistic()
{
	// Display all the player stat box at the right side
	// when player are playing the game
	// This will be in the game screen
	// This normally just be called once when the game is call
	TextColor(LIGHT_GREEN);
	displayBox(87, 17, 4, 15, "0");
	gotoxy(92, 18);
	cout << "SCORE";

	TextColor(LIGHT_RED);
	displayBox(102, 17, 4, 16, "5");
	gotoxy(106, 18);
	cout << "SHUFFLE";
}

void displayGameInstruction()
{
	// Display the Instruction for the player
	// This will appear in the game screen
	TextColor(AQUA);
	displayBox(87, 21, 9, 31, "");
	gotoxy(99, 22);
	TextColor(YELLOW);
	cout << "PLAYER";
	gotoxy(97, 23);
	cout << "INSTRUCTION";
	gotoxy(89, 25);
	TextColor(WHITE);
	cout << "H: HINT (-7 PTS)";
	gotoxy(89, 26);
	cout << "F: SHUFFLE";
	gotoxy(89, 27);
	cout << "ESC: BACK TO MENU";
	TextColor(WHITE);
}

int countDigits(int n)
{
	// Used to count the digits of number n
	int cnt = 0;
	if (n == 0) return 1;
	while (n > 0){
		cnt++;
		n /= 10;
	}
	return cnt;
}

void updateGameScore(int score)
{
	TextColor(LIGHT_GREEN);
	int scoreDigits = countDigits(score);
	// Here used to get the number of digits of score
	deleteBox(87 + (16 - scoreDigits) / 2, 19, 1, 4);
	gotoxy(87 + (16 - scoreDigits) / 2, 19); // x = cor_x + ((width_box - digitsOfScore) / 2)
	// Formula to get to the correct position to center the score
	// This goes with the displayGameStatistic func to update the score
	cout << score;
}

void updateShuffles(int shuffleCount)
{
	// Used to update the time of shuffles for player to see
	TextColor(LIGHT_RED);
	gotoxy(109, 19);
	cout << shuffleCount;
	TextColor(WHITE);
}

void displayWinGame(int time, int& choice)
{
	
	deleteBox(87, 21, 9, 31);
	// Delete the box because of the chance of getting overlaps
	TextColor(AQUA);
	displayBox(87, 21, 9, 31, "");
	// Set the box color to AQUA
	gotoxy(96, 22);
	TextColor(YELLOW);
	cout << "GAME FINISHED";

	gotoxy(97, 24);
	TextColor(WHITE);
	cout << "TIME PLAYED";
	gotoxy(101, 25);
	cout << time << "s";

	choice = 1;
	bool loop = true;
	// Set the initial choice to 1 to not get it out of controlled area
	
	while (loop)
	{
		if (choice == 1)
			TextColor(YELLOW);
		gotoxy(91, 27);
		cout << "NEW GAME";
		TextColor(WHITE);

		if (choice == 2)
			TextColor(YELLOW);
		gotoxy(108, 27);
		cout << "BACK";
		TextColor(WHITE);
		// Display NEW GAME or BACK in bright color based on choice

		switch (getConsoleInput())
		{
		case 4: // KEY_RIGHT
			choice++;
			if (choice > 2)
				choice = 1;
			break;

		case 3: // KEY_LEFT
			choice--;
			if (choice < 1)
				choice = 2;
			break;

		case 6: // KEY_ENTER or SPACEBAR
			PlaySound(TEXT("Select.wav"), NULL, SND_ASYNC);
			loop = false;
			break;
		}
	}
}

void displayContinueGame(int& choice) // Haven't change anything
{
	// This will appear when a saved game is encounter when player
	// choose a mode which has saved game
	deleteBox(53, 13, 3, 14);
	deleteBox(53, 17, 3, 14);
	deleteBox(53, 21, 3, 14);
	deleteBox(53, 25, 3, 14);
	// Delete the box of menu for better display
	gotoxy(48, 14);
	cout << "CONTINUE YOUR LAST GAME?";
	choice = 1;
	bool flag = true;
	while (flag)
	{
		if (choice == 1)
			TextColor(YELLOW);
		displayBox(53, 17, 3, 14, "YES");
		TextColor(WHITE);

		if (choice == 2)
			TextColor(YELLOW);
		displayBox(53, 21, 3, 14, "NO");
		TextColor(WHITE);
		// Display YES or NO in bright color based on choice

		switch (getConsoleInput())
		{
		case 2: // KEY_UP
			choice--;
			if (choice < 1)
				choice = 2;
			break;

		case 5: // KEY_DOWN
			choice++;
			if (choice > 2)
				choice = 1;
			break;

		case 6: // ENTER OR SPACEBAR
			PlaySound(TEXT("Select.wav"), NULL, SND_ASYNC);
			flag = false;
			break;
		}
	}
}

void displayConfirmQuit(int& choice)
{
	// This will appear when the player hit the ESC_KEY when inside the gaming screen
	deleteBox(87, 19, 11, 31);
	TextColor(AQUA);
	displayBox(87, 19, 11, 31, "");
	// Draw an AQUA box

	gotoxy(96, 23);
	TextColor(YELLOW);
	cout << "DO YOU WANT TO";
	gotoxy(98, 24);
	cout << "SAVE GAME?";
	TextColor(WHITE);
	choice = 1;
	bool loop = true;

	while (loop)
	{
		if (choice == 1)
			TextColor(YELLOW);
		gotoxy(93, 27);
		cout << "YES";
		TextColor(WHITE);

		if (choice == 2)
			TextColor(YELLOW);
		gotoxy(109, 27);
		cout << "NO";
		TextColor(WHITE);
		// Display YES or NO in bright color based on choice
		
		switch (getConsoleInput())
		{
		case 4: // KEY_RIGHT
			choice++;
			if (choice > 2)
				choice = 1;
			break;

		case 3: // KEY_LEFT
			choice--;
			if (choice < 1)
				choice = 2;
			break;

		case 6: // ENTER OR SPACEBAR
			PlaySound(TEXT("Select.wav"), NULL, SND_ASYNC);
			loop = false;
			break;
		}
	}
}

void displayMatchingLine(Pokemon p1, Pokemon p2, bool realBlock)
{	
	// Display a matching line only
	// This will be called when 2 pokemon is matched
	// realBlock is to check whether this is a matching type I
	// or called from other types of matching
	char c = 32;
	if (realBlock)
	{
		// If this is called from other function, this will cause the game to crash
		deleteBox(p1.x, p1.y, CELLS_HEIGHT, CELLS_WIDTH);
		deleteBox(p2.x, p2.y, CELLS_HEIGHT, CELLS_WIDTH);
	}
	if (p1.i == p2.i) // same row
	{
		if (p2.j < p1.j)
			swap(p1, p2); //p1 < p2

		for (int k = p1.x; k <= p2.x; k++)
		{
			TextColor(YELLOW * 16 + BLACK); // (background * 16 + text) color
			gotoxy(k + 5, p1.y + 2);  // gotoxy(k + CELLS_WIDTH / 2, p1.y + CELLS_HEIGHT / 2);
			cout << c;
		}
		TextColor(WHITE);
	}

	else if (p1.j == p2.j) // same column
	{
		if (p2.i < p1.i)
			swap(p1, p2); //p1 < p2

		for (int k = p1.y; k <= p2.y; k++)
		{
			TextColor(YELLOW * 16 + BLACK); // (background * 16 + text) color
			gotoxy(p1.x + 5, k + 2); // gotoxy(p1.x + CELLS_WIDTH / 2, k + CELLS_HEIGHT / 2);
			cout << c;
		}
		TextColor(WHITE);
	}
	if (realBlock)
	{
		// realBlock is used for better display
		// Display and delete more harmorny
		Sleep(300); // Time for the matching line to appear
		deleteMatchingLine(p1, p2);
	}
}

void deleteMatchingLine(Pokemon p1, Pokemon p2){
	// This is used after displayMatchingLine is called and we erase what it has draw
	if (p1.i == p2.i) // same row
	{
		if (p2.j < p1.j)
			swap(p1, p2); //p1 < p2
		deleteBox(p1.x + 5, p1.y + 2, 1, p2.x - p1.x + 1); // deleteBox(p1.x + CELLS_WIDTH / 2, p1.y + CELLS_HEIGHT / 2, matchingLineHeight, matchingLineWidth)
	}
	else if (p1.j == p2.j) // same column
	{
		if (p2.i < p1.i)
			swap(p1, p2); //p1 < p2
		deleteBox(p1.x + 5, p1.y + 2, p2.y - p1.y + 1, 1); // deleteBox(p1.x + CELLS_WIDTH / 2, p1.y + CELLS_HEIGHT / 2, matchingLineHeight, matchingLineWidth)
	}
}

void displayMatchingLineL(Pokemon p1, Pokemon p2, Pokemon corner)
{
	// This appear after 2 pokemons is matched, type L
	deleteBox(p1.x, p1.y, CELLS_HEIGHT, CELLS_WIDTH);
	deleteBox(p2.x, p2.y, CELLS_HEIGHT, CELLS_WIDTH);

	displayMatchingLine(p1, corner, false);
	displayMatchingLine(p2, corner, false);
	// Using the corner to draw a line from p1 to corner, corner to p2

	Sleep(300); // Time for the matching line to appear

	deleteMatchingLine(p1, corner);
	deleteMatchingLine(p2, corner);
	// Delete the drawn line
}

void displayMatchingLineUZ(Pokemon p1, Pokemon p2, Pokemon corner1, Pokemon corner2, Board gameBoard)
{
	// This appear when 2 pokemons is matched, type Z or U
	deleteBox(p1.x, p1.y, CELLS_HEIGHT, CELLS_WIDTH);
	deleteBox(p2.x, p2.y, CELLS_HEIGHT, CELLS_WIDTH);
	if (corner1.i == 0) // 2 corner is on the top side
	{	
		corner1.y = corner2.y = corner1.y + 1; // Make 2 corner lower in coordinate for better display 
	}
	else if (corner1.i == gameBoard.row + 1){ // 2 corner is on the bottom side
		corner1.y = corner2.y = corner1.y - 1; // Make 2 corner higher in coordinate for better display
	}
	else if (corner1.j == 0){ // 2 corner is on the left side
		corner1.x = corner2.x = corner1.x + 3; // Make 2 corner higher in coordinate for better display 
	}
	else if (corner1.j == gameBoard.col + 1){ // 2 corner is on the right side
		corner1.x = corner2.x = corner1.x - 3; // Make 2 corner lower in coordinate for better display 
	}
	displayMatchingLine(p1, corner1, false);
	displayMatchingLine(corner1, corner2, false);
	displayMatchingLine(p2, corner2, false);
	// Draw 3 lines using 2 corners to reconstruct the U or Z shape	

	Sleep(300); // Time for the lines to appear

	deleteMatchingLine(p1, corner1);
	deleteMatchingLine(corner1, corner2);
	deleteMatchingLine(p2, corner2);
	// Delete drawn lines
}

void displayGameOver(int& choice){
	// This appear when the player's shuffleCount reach 0
	// and there is no more pokemon matches available
	deleteBox(87, 21, 9, 31);
	// Delete box to not get overlaps
	TextColor(AQUA);
	displayBox(87, 21, 9, 31, "");
	gotoxy(98, 22);
	TextColor(RED);
	cout << "GAME OVER";

	gotoxy(93, 24);
	cout << "RUN OUT OF SHUFFLES";

	choice = 1;
	bool loop = true;

	while (loop)
	{
		if (choice == 1)
			TextColor(YELLOW);
		gotoxy(91, 27);
		cout << "NEW GAME";
		TextColor(WHITE);

		if (choice == 2)
			TextColor(YELLOW);
		gotoxy(108, 27);
		cout << "BACK";
		TextColor(WHITE);
		// Display NEW GAME or BACK in bright color based on choice

		switch (getConsoleInput())
		{
		case 4: // KEY_RIGHT
			choice++;
			if (choice > 2)
				choice = 1;
			break;

		case 3: // KEY_LEFT
			choice--;
			if (choice < 1)
				choice = 2;
			break;

		case 6: // ENTER or SPACEBAR
			PlaySound(TEXT("Select.wav"), NULL, SND_ASYNC);
			loop = false;
			break;
		}
	}
}

void displayRunOutOfShuffle(){
	// This will appear when player run out of shuffle times
	deleteBox(87, 21, 9, 31);
	// Delete box to not get overlaps
    TextColor(YELLOW);
    displayBox(87, 21, 9, 31, "");
	gotoxy(92, 24);
	cout << "RUN OUT OF SHUFFLES!";
	gotoxy(96, 26);
	cout << "CAN'T SHUFFLE";
}

bool readyInstructionMemoryMode()
{
	// This will appear when player choose the MEMORY mode from menu screen
	system("cls");
    TextColor(YELLOW);
    gotoxy(0, 1);
    cout << R"(
                                                ____   __  __ __     ______
                                               / __ \ / / / // /    / ____/
                                              / /_/ // / / // /    / __/   
                                             / _, _// /_/ // /___ / /___   
                                            /_/ |_| \____//_____//_____/   
                              
    )";
    TextColor(WHITE);
    displayBox(6, 8, 17, 108, "");
    gotoxy(9, 12);
    cout << "IN THIS GAMEMODE, YOU WILL HAVE 5 SECONDS TO REMEMBER ALL THE POKEMONS BEFORE IT DISAPEARS";
    gotoxy(9, 14);
    cout << "THE POKEMONS WILL ONLY REAPPEAR WHEN YOU:";
    gotoxy(34, 17);
    cout << "SHUFFLE:";
	gotoxy(60, 17);
	cout << "APPEAR FOR 5 SECONDS";
    gotoxy(15, 19);
    cout << "CORRECTLY MATCH 2 POKEMONS:";
	gotoxy(60, 19);
	cout << "APPEAR FOR 4 SECONDS";
	// Instructions for MEMORY mode
    int choice = 1;
	bool flag = true;
	while (flag)
	{
		if (choice == 1)
			TextColor(YELLOW);
		displayBox(32, 26, 3, 14, "BACK");
		TextColor(WHITE);

		if (choice == 2)
			TextColor(YELLOW);
		displayBox(75, 26, 3, 14, "READY!");
		TextColor(WHITE);
		// Display BACK or READY! in bright color based on choice

		switch (getConsoleInput())
		{
		case 3: // KEY_LEFT
			choice--;
			if (choice < 1)
				choice = 2;
			break;

		case 4: // KEY_RIGHT
			choice++;
			if (choice > 2)
				choice = 1;
			break;

		case 6: // ENTER or SPACEBAR
			PlaySound(TEXT("Select.wav"), NULL, SND_ASYNC);
			switch (choice)
			{
				case 1: // BACK
					PlaySound(TEXT("Menu.wav"), NULL, SND_ASYNC | SND_LOOP);
					return false;
				
				case 2: // READY
					return true;
				// Return which key is pressed
			}
		}
	}
}
