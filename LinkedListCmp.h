#pragma once
#include <iostream>

using namespace std;

struct Cell {
    int data; // stored the board's pokemon
    Cell* next = nullptr;
};

void pushCell(Cell*& head, Cell* newNode);

void removeCellLocation(Cell** arr, int deletePosRow, int deletePosCol);

void deallocateCell(Cell**& arr, int row);

Cell** transferBoardToLinkedList(int** board, int row, int col);

void transferLinkedlistToBoard(Cell** arr, int** &board, int row, int col);

void removePokemonHard(int** &board, int deletePosRow, int deletePosCol);