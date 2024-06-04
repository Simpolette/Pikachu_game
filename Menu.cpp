#include "Menu.h"

void interactWithMenu(vector <Player*> list, int playerPos)
{
    int** board = NULL;

BACK_TO_MENU:
    TextColor(WHITE);
    displayMenuScreen();
    // Display the logo
    Board gameBoard;
    int choice = 1;
    bool menuLoop = true;
    while (menuLoop)
    {
        if (choice == 1)
            TextColor(YELLOW);
        displayBox(53, 13, 3, 14, "PLAY");
        TextColor(WHITE);

        if (choice == 2)
            TextColor(YELLOW);
        displayBox(53, 17, 3, 14, "RANK");
        TextColor(WHITE);

        if (choice == 3)
            TextColor(YELLOW);
        displayBox(53, 21, 3, 14, "HELP");
        TextColor(WHITE);

        if (choice == 4)
            TextColor(YELLOW);
        displayBox(53, 25, 3, 14, "EXIT");
        TextColor(WHITE);
        // Display which one is being choose based on choice

        switch (getConsoleInput())
        {
            case 2: // KEY_UP
                choice--;
                if (choice < 1) choice = 4; // if the user goes past the first option, loop back to the last option
                break;
            
            case 5: // KEY_DOWN
                choice++;
                if (choice > 4) choice = 1; // if the user goes past the last option, loop back to the first option
                break;
            
            case 6: // ENTER or SPACEBAR
                PlaySound(TEXT("Menu.wav"), NULL, SND_ASYNC | SND_LOOP);
                switch (choice)
                {
                case 1: // PLAY
                    choice = 1;
                    while (menuLoop)
                    {
                        if (choice == 1)
                            TextColor(YELLOW);
                        displayBox(53, 13, 3, 14, "EASY");
                        TextColor(WHITE);

                        if (choice == 2)
                            TextColor(YELLOW);
                        displayBox(53, 17, 3, 14, "HARD");
                        TextColor(WHITE);

                        if (choice == 3)
                            TextColor(YELLOW);
                        displayBox(53, 21, 3, 14, "MEMORY");
                        TextColor(WHITE);

                        if (choice == 4)
                            TextColor(YELLOW);
                        displayBox(53, 25, 3, 14, "BACK");
                        TextColor(WHITE);
                        // Display which one is being choose based on choice

                        switch (getConsoleInput())
                        {
                            case 2: // KEY_UP
                                choice--;
                                if (choice < 1) choice = 4;
                                break;

                            case 5: // KEY_DOWN
                                choice++;
                                if (choice > 4) choice = 1;
                                break;

                            case 6: // ENTER or SPACEBAR

                                PlaySound(TEXT("Select.wav"), NULL, SND_ASYNC);

                                switch (choice)
                                {
                                    case 1: //EASY MODE                               
                                        Gameplay(board, EASY, gameBoard, list, playerPos);
                                        deleteBoard(board, gameBoard);

                                        system("cls");
                                        goto BACK_TO_MENU;

                                    case 2: // HARD MODE                         
                                        Gameplay(board, HARD, gameBoard, list, playerPos);
                                        deleteBoard(board, gameBoard);

                                        system("cls");
                                        goto BACK_TO_MENU;

                                    case 3: //MEMORY MODE
                                        GameplayMemory(board, gameBoard, list, playerPos);
                                        deleteBoard(board, gameBoard);

                                        system("cls");
                                        goto BACK_TO_MENU;

                                    case 4: // BACK
                                        PlaySound(TEXT("Menu.wav"), NULL, SND_ASYNC | SND_LOOP);
                                        deleteBox(53, 21, 3, 14); // Delete to not get the MEMORY overlaps on HELP
                                        goto BACK_TO_MENU;
                                        break;
                                }
                        }
                    }
                    gotoxy(0, 40);
                    system("pause");
                    menuLoop = false;
                    break;

                case 2: // RANKING
                    system("cls");
                    rankingScreen(list);
                    goto BACK_TO_MENU;
                    break;

                case 3: //HELP
                    system("cls");
                    helpScreen();
                    goto BACK_TO_MENU;
                    break;

                case 4: //EXIT
                    outputInfoPlayer(list, "Player.txt", gameBoard);
                    system("cls");
                    exit(0);
                    break;
                }
        }
    }
    deleteList(list);
}

void getLoginInfo(string& userName, string& password, bool& escapeMenu)
{
    // This will appear when player choose NEW PLAYER or EXISTING PLAYER from menu screen
    // Getting username and password with _getch()
    escapeMenu = false;
    bool userNameFlag = true;
    TextColor(RED);
    gotoxy(48, 29);
    cout << "Press 'ESC' to go back";
    TextColor(WHITE);
    gotoxy(44, 15);
    cout << "USERNAME: ";
    displayBox(53, 14, 3, 20, "");
    // Box for player input of username
    gotoxy(55, 15); // Go to input place
    while (userNameFlag)
    {
        int input = _getch();
        if (input == 27) // ESC key
        { 
            escapeMenu = true;
            return;
        }
        else if ((input == '\r' || input == '\n') && userName.length() != 0) // Enter key
        { 
            userNameFlag = false;
        } 
        else if (input == '\b') // Backspace key
        { 
            if (!userName.empty())
            {
                // Check if username is empty or not then player can hit backspace to delete the previous character
                userName.pop_back();
                cout << "\b \b";
                // '\b' is to go back one
                // ' ' is to erase the character
                // '\b' is to go back one
                // Combine, you represent the action of backspace
            }
        }
        else if (userName.length() > 15) // If player input > 15 stop accepting input
        {
            continue;
        }
        else if ((input >= '0' && input <= '9') || (input >= 'a' && input <= 'z') || (input >= 'A' && input <= 'Z'))
        {
            userName += input;
            cout << char(input);
        }
    }

    gotoxy(44, 18);
    cout << "PASSWORD: ";
    displayBox(53, 17, 3, 20, "");
    gotoxy(55, 18);
    bool passwordFlag = true;
    while (passwordFlag)
    {
        int input = _getch();
        if (input == 27) // ESC key
        { 
            escapeMenu = true;
            return;
        }
        else if ((input == '\r' || input == '\n') &&  password.length() != 0) // Enter key
        { 
            passwordFlag = false;
        } 
        else if (input == '\b') // Backspace key
        { 
            if (!password.empty())
            {
                password.pop_back();
                cout << "\b \b";
            }
        }
        else if (password.length() > 15)
        {
            continue;
        }
        else if ((input >= '0' && input <= '9') || (input >= 'a' && input <= 'z') || (input >= 'A' && input <= 'Z'))
        {
            password += input;
            cout << '*';
        }
    }
}

void IntroScreen()
{
    // This will appear when player open the game
    PlaySound(TEXT("Menu.wav"), NULL, SND_ASYNC | SND_LOOP);
    ShowConsoleCursor(0);
    for (int i = 1; i < 14; i++)
    {
        TextColor(i); // Change the color of logo
        displayLogo(18, 1);
        Sleep(300); // Time for each blink of logo
    }
    TextColor(YELLOW);
    displayLogo(18, 1);
}

void loginScreen(vector <Player*>& list, int& playerPos)
{   
    // The very first screen to appear
    Board gameBoard;
    loadInfoPlayer(list, "Player.txt", gameBoard);
    // Load in saved player info from "Player.txt"
    int choice = 1;
    bool loop = true;
    while (loop)
    {
        displayMenuScreen();
        // Display the logo

        if (choice == 1)
            TextColor(YELLOW);
        displayBox(50, 13, 3, 20, "NEW PLAYER");
        TextColor(WHITE);

        if (choice == 2)
            TextColor(YELLOW);
        displayBox(50, 17, 3, 20, "EXISTING PLAYER");
        TextColor(WHITE);

        if (choice == 3)
            TextColor(YELLOW);
        displayBox(50, 21, 3, 20, "EXIT");
        TextColor(WHITE);
        // Display which one is being choose based on choice

        switch (getConsoleInput())
        {
        case 2: // KEY_UP
            choice--;
            if (choice < 1)
                choice = 3;
            break;

        case 5: // KEY_DOWN
            choice++;
            if (choice > 3)
                choice = 1;
            break;

        case 6: // ENTER or SPACEBAR
            PlaySound(TEXT("Menu.wav"), NULL, SND_ASYNC | SND_LOOP);

            deleteBox(50, 13, 3, 20);
            deleteBox(50, 17, 3, 20);
            deleteBox(50, 21, 3, 20);
            // Delete the "NEW PLAYER", "EXISTING PLAYER", "EXIT" box

            displayPokeball(1, 12, RED);
            displayPokeball(11, 17, BLUE);
            displayPokeball(93, 12, BLUE);
            displayPokeball(83, 17, RED);
            // Display Pokeballs

            bool flag = true;
            while (flag)
            {
                if (choice == 3) // EXIT
                {
                    system("cls");
                    exit(0);
                }
                else
                {
                    GET_ACCOUNT:
                    gotoxy(48, 21);
                    ShowConsoleCursor(1);
                    string userName = "";
                    string password = "";
                    bool escapeMenu;

                    getLoginInfo(userName, password, escapeMenu);
                    // Get the player username and passworod

                    if (escapeMenu)
                    {
                        // If key pressed from getLoginInfo is ESC
                        // Return to the login screen
                        system("cls");
                        flag = false;
                        break;
                    }

                    if (choice == 1) // NEW PLAYER
                    {
                        if (checkAvailableUserName(list, userName)) // New player
                        {
                            addNewPlayerToList(list, userName, password, gameBoard); // Add player
                            playerPos = posPlayerInList(list, userName); // Get player pos from list
                            flag = false;
                            loop = false;
                            system("cls");
                        }
                        else
                        {
                            PlaySound(TEXT("Menu.wav"), NULL, SND_ASYNC | SND_LOOP);
                            deleteBox(53, 17, 3, 20); // Delete the password box
                            deleteBox(44, 18, 1, 9); // Delete word
                            deleteBox(55, 15, 1, 16); // Delete input username
                            gotoxy(34, 27);
                            TextColor(LIGHT_RED);
                            cout << "This name already exists, please choose another name";
                            ShowConsoleCursor(0);
                            Sleep(1000); // Time for "This name..." to appear
                            deleteBox(34, 27, 1, 55); // Delete the "This name..." line
                            TextColor(WHITE);
                            goto GET_ACCOUNT;
                        }
                    }

                    else if (choice == 2) // EXISTING PLAYER
                    {
                        if (checkCorrectAccount(list, userName, password)) // Exist player
                        {
                            PlaySound(TEXT("Menu.wav"), NULL, SND_ASYNC | SND_LOOP);
                            playerPos = posPlayerInList(list, userName);
                            ShowConsoleCursor(0);
                            TextColor(YELLOW);
                            deleteBox(46, 17, 6, 28); // Delete box to not get overlaps
                            displayBox(46, 17, 6, 28, list[playerPos]->userName);
                            // Display box for WELCOME BACK with player name
                            gotoxy(54, 19);
                            cout << "WELCOME BACK";
                            Sleep(2000); // Time for "WELCOME BACK" box to appear
                            TextColor(WHITE);

                            flag = false;
                            loop = false;
                            system("cls");
                        }
                        else 
                        {
                            // Wrong password or username does not exist
                            PlaySound(TEXT("Menu.wav"), NULL, SND_ASYNC | SND_LOOP);
                            deleteBox(53, 17, 3, 20); // Delete the password box
                            deleteBox(44, 18, 1, 9); // Delete word
                            deleteBox(55, 15, 1, 16); // Delete input username
                            gotoxy(39, 27);
                            TextColor(LIGHT_RED);
                            cout << "Please check your username and password again!";
                            ShowConsoleCursor(0);
                            Sleep(1000); // Time for "Please..." to exist
                            deleteBox(39, 27, 1, 46); // Delete "Please..." line
                            TextColor(WHITE);
                            goto GET_ACCOUNT;
                        }
                    }
                    

                }
            }
            ShowConsoleCursor(0);
        }
    }
}

void helpScreen()
{
    // This will appear when player choose HELP in menu screen
    TextColor(WHITE);
    displayBox(2, 3, 20, 38, "");
    // Display box for "CONTROL KEYS"
    gotoxy(15, 5);
    TextColor(YELLOW);
    cout << "CONTROL KEYS";
    TextColor(WHITE);
    gotoxy(5, 8);
    cout << "ARROW KEYS/ WASD: MOVEMENT KEYS"; 
    gotoxy(5, 10);
    cout << "SPACE/ ENTER: SELECT POKEMON";
    gotoxy(5, 12);
    cout << "F: SHUFFLE THE BOARD";
    gotoxy(5, 14);
    cout << "H: HINT (MOVE SUGGESTION)";
    gotoxy(5, 16);
    cout << "ESC: QUIT GAME, BACK TO MENU";

    displayBox(41, 3, 20, 38, "");
    // Display box for "GAME RULES"
    gotoxy(55, 5);
    TextColor(YELLOW);
    cout << "GAME RULES";
    TextColor(WHITE);
    gotoxy(43, 8);
    cout << "  . YOUR OBJECTIVE IN THIS GAME ";
    gotoxy(43, 9);
    cout << "IS FINDING A PAIR OF POKEMON AND";
    gotoxy(43, 10);
    cout << "MATCHING THEM!";
    gotoxy(43, 12);
    cout << "  . TWO IDENTICAL POKEMONS ARE";
    gotoxy(43, 13);
    cout << "MATCHED BY I, U, L, Z LINE AND";
    gotoxy(43, 14);
    cout << "THERE MUST BE NO OBSTACLES BETWEEN";
    gotoxy(43, 15);
    cout << "THEM.";
    gotoxy(43, 17);
    cout << "  . YOU WILL WIN THE GAME WHEN";
    gotoxy(43, 18);
    cout << "THERE IS NO POKEMON LEFT.";

    displayBox(80, 3, 20, 38, "");
    // Display box for "SCORE CALCULATION"
    gotoxy(91, 5);
    TextColor(YELLOW);
    cout << "SCORE CALCULATION";
    TextColor(WHITE);
    gotoxy(90, 8);
    cout << "MATCHING I: 1 POINT";
    gotoxy(90, 10);
    cout << "MATCHING L: 3 POINT";
    gotoxy(90, 12);
    cout << "MATCHING U: 5 POINT";
    gotoxy(90, 14);
    cout << "MATCHING Z: 5 POINT";
    gotoxy(90, 16);
    cout << "HINT      : -7 POINT";

    TextColor(YELLOW);
    displayBox(57, 24, 3, 8, "BACK");
    TextColor(WHITE);
    // Represent of a way back for player

RETURN:
    int input = getConsoleInput();

    if (input == 6 || input == 1) // SPACEBAR or ENTER or ESC
    {
        PlaySound(TEXT("Menu.wav"), NULL, SND_ASYNC | SND_LOOP);
        system("cls");
        displayMenuScreen();
    }
    else
    {
        goto RETURN;
    }
}

void rankingScreen(vector <Player*> list)
{
    // This will appear when player choose ranking in the menu screen
RANKING_SCREEN:
    TextColor(YELLOW);
    gotoxy(0, 1);
    cout << R"(
                                        ____   ___     _   __ __ __  ____ _   __ ______
                                       / __ \ /   |   / | / // //_/ /  _// | / // ____/
                                      / /_/ // /| |  /  |/ // ,<    / / /  |/ // / __  
                                     / _, _// ___ | / /|  // /| | _/ / / /|  // /_/ /  
                                    /_/ |_|/_/  |_|/_/ |_//_/ |_|/___//_/ |_/ \____/  
    )";
    // width sceen is 120
    int choice = 1;
    bool loop = true;
    while (loop)
    {
        if (choice == 1)
            TextColor(YELLOW);
        displayBox(50, 13, 3, 19, "EASY MODE");
        TextColor(WHITE);

        if (choice == 2)
            TextColor(YELLOW);
        displayBox(50, 17, 3, 19, "HARD MODE");
        TextColor(WHITE);

        if (choice == 3)
            TextColor(YELLOW);
        displayBox(50, 21, 3, 19, "MEMORY MODE");
        TextColor(WHITE);

        if (choice == 4)
            TextColor(YELLOW);
        displayBox(50, 25, 3, 19, "BACK");
        TextColor(WHITE);
        // Display which one is being choose based on choice

        switch (getConsoleInput())
        {
        case 2: // KEY_UP
            choice--;
            if (choice < 1)
                choice = 4;
            break;

        case 5: // KEY_DOWN
            choice++;
            if (choice > 4)
                choice = 1;
            break;

        case 6: // ENTER or SPACEBAR
            switch(choice)
            {
                case 1:
                    PlaySound(TEXT("Menu.wav"), NULL, SND_ASYNC | SND_LOOP);
                    system("cls");
                    rankingEasyScreen(list);
                    goto RANKING_SCREEN;
                    break;
                case 2:
                    PlaySound(TEXT("Menu.wav"), NULL, SND_ASYNC | SND_LOOP);
                    system("cls");
                    rankingHardScreen(list);
                    goto RANKING_SCREEN;
                    break;
                case 3:
                    PlaySound(TEXT("Menu.wav"), NULL, SND_ASYNC | SND_LOOP);
                    system("cls");
                    rankingMemoryScreen(list);
                    goto RANKING_SCREEN;
                    break;
                case 4:
                    PlaySound(TEXT("Menu.wav"), NULL, SND_ASYNC | SND_LOOP);
                    system("cls");
                    loop = false;
                    break;
                // Choose which screen to display based on choice
            }
        }
    }
}

void rankingEasyScreen(vector <Player*> list)
{
    // This will appear when player choose EASY MODE in ranking screen
    TextColor(YELLOW);
    gotoxy(0, 1);
    cout << R"(
                                                ______ ___    _______  __
                                               / ____//   |  / ___/\ \/ /
                                              / __/  / /| |  \__ \  \  / 
                                             / /___ / ___ | ___/ /  / /  
                                            /_____//_/  |_|/____/  /_/  
    )";
    displayBox(56, 26, 3, 8, "BACK");
    // A represent to a way back for the player
    TextColor(WHITE);
    displayBox(2, 8, 17, 56, "");
    displayBox(62, 8, 17, 56, "");
    // The 2 box that contain BEST TIME and HIGH SCORE

    TextColor(YELLOW);
    gotoxy(26, 10);
    cout << "BEST TIME";
    gotoxy(86, 10);
    cout << "HIGH SCORE";
    TextColor(WHITE);

    sortPlayerScoreEasy(list);
    sortPlayerTimeEasy(list);
    // Used to display the first 3 in the ranking board

    RETURN:
        int input = getConsoleInput();

        if (input == 6 || input == 1) // SPACEBAR or ENTER or ESC
        {
            PlaySound(TEXT("Menu.wav"), NULL, SND_ASYNC | SND_LOOP);
            system("cls");
            return;
        }
        else
        {
            goto RETURN;
        }
}

void rankingHardScreen(vector <Player*> list)
{
    // This will appear when player choose HARD MODE in ranking screen
    TextColor(YELLOW);
    gotoxy(0, 1);
    cout << R"(
                                                __  __ ___     ____   ____ 
                                               / / / //   |   / __ \ / __ \
                                              / /_/ // /| |  / /_/ // / / /
                                             / __  // ___ | / _, _// /_/ / 
                                            /_/ /_//_/  |_|/_/ |_|/_____/  
    )";
    displayBox(56, 26, 3, 8, "BACK");
    // A represent to a way back for the player
    TextColor(WHITE);
    displayBox(2, 8, 17, 56, "");
    displayBox(62, 8, 17, 56, "");
    // The 2 box that contain BEST TIME and HIGH SCORE

    TextColor(YELLOW);
    gotoxy(26, 10);
    cout << "BEST TIME";
    gotoxy(86, 10);
    cout << "HIGH SCORE";
    TextColor(WHITE);

    sortPlayerScoreHard(list);
    sortPlayerTimeHard(list);
    // Used to display the first 3 in the ranking board

    RETURN:
        int input = getConsoleInput();

        if (input == 6 || input == 1) // SPACEBAR or ENTER or ESC
        {
            PlaySound(TEXT("Menu.wav"), NULL, SND_ASYNC | SND_LOOP);
            system("cls");
            return;
        }
        else
        {
            goto RETURN;
        }
}

void rankingMemoryScreen(vector <Player*> list)
{
    // This will appear when player choose MEMORY MODE in ranking screen
    TextColor(YELLOW);
    gotoxy(0, 1);
    cout << R"(
                                            __  ___ ______ __  ___ ____   ____ __  __
                                           /  |/  // ____//  |/  // __ \ / __ \\ \/ /
                                          / /|_/ // __/  / /|_/ // / / // /_/ / \  / 
                                         / /  / // /___ / /  / // /_/ // _, _/  / /  
                                        /_/  /_//_____//_/  /_/ \____//_/ |_|  /_/   
                                             
    )";
    displayBox(56, 26, 3, 8, "BACK");
    // A represent to a way back for the player
    TextColor(WHITE);
    displayBox(2, 8, 17, 56, "");
    displayBox(62, 8, 17, 56, "");
    // The 2 box that contain BEST TIME and HIGH SCORE

    TextColor(YELLOW);
    gotoxy(26, 10);
    cout << "BEST TIME";
    gotoxy(86, 10);
    cout << "HIGH SCORE";
    TextColor(WHITE);

    sortPlayerScoreMemory(list);
    sortPlayerTimeMemory(list);
    // Used to display the first 3 in the ranking board

    RETURN:
        int input = getConsoleInput();

        if (input == 6 || input == 1) // SPACEBAR or ENTER or ESC
        {
            PlaySound(TEXT("Menu.wav"), NULL, SND_ASYNC | SND_LOOP);
            system("cls");
            return;
        }
        else
        {
            goto RETURN;
        }
}
