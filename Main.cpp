#include "Menu.h"

int main()
{
    srand(time(0));
    vector <Player*> list;
    // Create the list
    int playerPos;
    IntroScreen();
    loginScreen(list, playerPos);
    interactWithMenu(list, playerPos);
    return 0;
}
