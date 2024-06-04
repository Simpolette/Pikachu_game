#pragma once

#include "Struct.h"
#include "Display.h"
#include "Player.h"
#include "LinkedListCmp.h"
#include <vector>
#include <random>

using namespace std;

string* createBackground();
void getBackground(string fileName, string* background);
void createBoard(int**& board, Board gameBoard); 
void createPoint(int**& board, Board gameBoard); 
void deletePoint(int** board, Pokemon p1, Pokemon p2, int mode);
bool validPoke(int** board, Pokemon p1, Pokemon p2);
bool matchingI(int** board, Pokemon p1, Pokemon p2);
bool matchingL(int** board, Pokemon p1, Pokemon p2, Pokemon& corner);
bool matchingUZ(int** board, Pokemon& p1, Pokemon& p2, Pokemon& corner1, Pokemon& corner2, Board gameBoard);
bool checkMatchingAndDisplay(int** board, Pokemon p1, Pokemon p2, int& point, Board gameBoard, string* background, int mode);
bool checkMatching(int** board, Pokemon p1, Pokemon p2, Board gameBoard);
bool checkContinue(int** board, Pokemon& p1, Pokemon& p2, Board gameBoard);
void shuffleBoard(int** board, Board gameBoard);
void Gameplay(int**& board, int mode, Board& gameBoard, vector <Player*> list, int playerPos);
void GameplayMemory(int**& board, Board& gameBoard, vector <Player*> list, int playerPos);
void deleteBoard(int**& board, Board gameBoard);
void deleteBackground(string* background);