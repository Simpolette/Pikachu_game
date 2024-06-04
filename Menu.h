#pragma once

#include "Display.h"
#include "Gameplay.h"
#include "Player.h"

using namespace std;

void interactWithMenu(vector <Player*> list, int playerPos);
void IntroScreen();
void loginScreen(vector <Player*>& list, int& playerPos);
void helpScreen();
void rankingScreen(vector <Player*> list);  
void getLoginInfo(string& userName, string& password, bool& escapeMenu);
void rankingEasyScreen(vector <Player*> list);
void rankingHardScreen(vector <Player*> list);
void rankingMemoryScreen(vector <Player*> list);
