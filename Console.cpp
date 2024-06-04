#include "Console.h"

void gotoxy(int x, int y)
{
	// Go to the coordinate (x, y) on console
    COORD pos = { x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void TextColor(int x)
{
	// Change the text colour to x, some color has been defined
	// We can change the background of text with the formula:
	// x = background_color * 16 + text_color
	// On default, background color is black
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, x);
}

void ShowConsoleCursor(bool showFlag) // 1 is to show, 0 is to not
{
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO cursorInfo;

    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showFlag; // Set the cursor visibility
    SetConsoleCursorInfo(out, &cursorInfo);
}

int getConsoleInput() // Learn from Louis
{
    int c = _getch();
	// Arrow key
	if (c == 0 || c == 224) // To get special keys
	{
		switch (_getch())
		{
		case KEY_UP:				// UP
			return 2;
		case KEY_LEFT:				// LEFT
			return 3;
		case KEY_RIGHT:				// RIGHT
			return 4;
		case KEY_DOWN:				// DOWN
			return 5;
		default:				// OTHER BUTTONS
			return 0;
		}
	}
	else
	{
		if (c == KEY_ESC)
			return 1;
		else if (c == 87 || c == 119) // W, w
			return 2;
		else if (c == 65 || c == 97)  // A, a
			return 3;
		else if (c == 68 || c == 100) // D, d
			return 4;
		else if (c == 83 || c == 115) // S, s
			return 5;
		else if (c == ENTER || c == SPACE_BAR)
			return 6;
		else if (c == 72 || c == 104) // H, h
			return 7;
		else if (c == 70 || c == 102) // F, f
			return 8;
		else
			return 0;                 // OTHER BUTTONS
	}
}