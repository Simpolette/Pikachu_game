#pragma once

#include "Struct.h"
#include "Console.h"
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

bool checkAvailableUserName(vector <Player*> list, string userName);
bool checkCorrectAccount(vector <Player*> list, string userName, string password);
void addNewPlayerToList(vector <Player*>& list, string userName, string password, Board gameBoard);
int posPlayerInList(vector <Player*>& list, string userName);
void copyBoardEasy(vector <Player*> list, int pos, int** board, Board gameBoard);
void copyBoardHard(vector <Player*> list, int pos, int** board, Board gameBoard);
void copyBoardMemory(vector <Player*> list, int pos, int** board, Board gameBoard);
void copyBoard(int** mainBoard, int** board, Board gameBoard);

void outputInfoPlayer(vector <Player*> list, string nameFile, Board gameBoard);
void loadInfoPlayer(vector <Player*>& list, string nameFile, Board gameBoard);

bool comparePlayerScoreEasy(Player* p1, Player* p2);
bool comparePlayerScoreHard(Player* p1, Player* p2);
bool comparePlayerScoreMemory(Player* p1, Player* p2);
void sortPlayerScoreEasy(vector <Player*> list);
void sortPlayerScoreHard(vector <Player*> list);
void sortPlayerScoreMemory(vector <Player*> list);

bool comparePlayerTimeEasy(Player* p1, Player* p2);
bool comparePlayerTimeHard(Player* p1, Player* p2);
bool comparePlayerTimeMemory(Player* p1, Player* p2);
void sortPlayerTimeEasy(vector <Player*> list);
void sortPlayerTimeHard(vector <Player*> list);
void sortPlayerTimeMemory(vector <Player*> list);

void deleteList(vector <Player*> list);