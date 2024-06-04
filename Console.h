#pragma once
#pragma comment(lib, "winmm.lib") // To include the winmm.lib library

#include <Windows.h>
#include <conio.h>

// KEYS
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_ESC 27
#define SPACE_BAR 32
#define ENTER 13
#define KEY_F 102
#define KEY_H 104

// COLOUR
#define BLACK 0
#define BLUE 1
#define GREEN 2
#define AQUA 3
#define RED 4
#define PURPLE 5
#define YELLOW 6
#define WHITE 7
#define GRAY 8
#define LIGHT_BLUE 9
#define LIGHT_GREEN 10
#define LIGHT_AQUA 11
#define LIGHT_RED 12
#define LIGHT_PURPLE 13
#define LIGHT_YELLOW 14
#define BRIGHT_WHITE 15

void gotoxy(int x, int y);
void TextColor(int x);
void ShowConsoleCursor(bool showFlag); // 0 = Hide cursor, 1 = Show cursor.
int getConsoleInput();