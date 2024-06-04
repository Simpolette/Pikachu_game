#pragma once

#include "Console.h"
#include "Struct.h"
#include <string>
#include <vector>
#include <iostream>
#include <conio.h> // <----- Library for _getch()
#include <fstream>

using namespace std;

// HEIGHT, WIDTH OF EACH CELLS
const int CELLS_HEIGHT = 5;
const int CELLS_WIDTH = 10;

// STARTING CORNER OF GAMEBOARD
const int STARTING_X = 4;
const int STARTING_Y = 3;

// MOVEMENT
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_ENTER 13
#define KEY_ESC 27
#define SPACE_BAR 32
#define KEY_F 102
#define KEY_H 104
#define KEY_S 115

void displayBox(int x, int y, int boxHeight, int boxWidth, string s);
void displayChosenBox(int x, int y, int boxHeight, int boxWidth, char s, int background, int text);
void displayLogo(int x, int y);
void displayMenuScreen();
void displayGameBox(int x, int y, int boxHeight, int boxWidth, int** board, Board gameBoard, string* background, int mode);
void displayAllChar(int x, int y, int boxHeight, int boxWidth, int** board, Board gameBoard);
void displayEraseAllChar(int x, int y, int boxHeight, int boxWidth, int** board, Board gameBoard);
void displayPokeball(int x, int y, int ball_color);
void deleteBox(int x, int y, int boxHeight, int boxWidth);
void displayBoxChar(int x, int y, int boxHeight, int boxWidth, char s);
void displayPlayerInfo(vector <Player*> list, int playerPos);
void displayGameStatistic();
void displayGameInstruction();
void updateGameScore(int score);
void updateShuffles(int shuffleCount);
void displayWinGame(int time, int& choice);
void displayConfirmQuit(int& choice);
void displayContinueGame(int& choice);
void displayMatchingLine(Pokemon p1, Pokemon p2, bool realBlock);
void deleteMatchingLine(Pokemon p1, Pokemon p2);
void displayMatchingLineL(Pokemon p1, Pokemon p2, Pokemon corner);
void displayMatchingLineUZ(Pokemon p1, Pokemon p2, Pokemon corner1, Pokemon corner2, Board gameBoard);
void background_upgrade(int pX, int pY, string* background, int mode);
void background_upgrade_line(Pokemon p1, Pokemon p2, string* background, int mode);
void displayGameOver(int& choice);
void displayRunOutOfShuffle();
bool readyInstructionMemoryMode();