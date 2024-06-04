#pragma once

#include <iostream>
#include <ctime>

#define EASY 0
#define HARD 1
#define MEMORY 2

struct Board
{
    int col = 8;
    int row = 5;
    int width; //col * cell width
    int height; //row * cell Height
};

struct Pokemon 
{
    int i; //index
    int j;

    int x; //coordinate
    int y; // x = 4 + (j - 1) * 10, 3 + (i - 1) * 5
};

struct InforMatches
{
    int bestScore = 0;
    int bestTime = 0;
    int score = 0;
    int pokemon = 0;
    int time = 0;
    int shuffleCount = 5;
    int** board = NULL;
    bool gameSavedCheck = 0;
    int row;
    InforMatches(int row, int col)
    {
        board = new int*[row];
        for (int i = 0; i < row; ++i)
        {   
            board[i] = new int[col];
            for (int j = 0; j < col; ++j)
            {
                board[i][j] = 0;
            }
        }
    }

    ~InforMatches()
    {
        for (int i = 0; i < row; ++i)
        {
            delete[] board[i];
        }
        delete[] board;
    }

};

struct Player
{
    std::string userName;
    std::string password;
    InforMatches* Easy;
    InforMatches* Hard;
    InforMatches* Memory;

    ~Player()
    {
        delete Easy;
        delete Hard;
        delete Memory;
    }
};