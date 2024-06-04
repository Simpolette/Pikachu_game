#include "LinkedListCmp.h"

//  This file is used mainly in Gameplay.cpp/ deletePoint function

void pushCell(Cell*& head, Cell* newNode)
{
    // This is to push a Cell in a linked list row
    if (head == nullptr)
    {
        head = newNode;
    }
    else
    {
        Cell* current = head;
        while (current->next != nullptr)
        {
            current = current->next;
        }
        current->next = newNode;
    }
}

void removeCellLocation(Cell** arr, int deletePosRow, int deletePosCol)
{
    // This is to remove a specific cell at the location
    Cell* tmp = arr[deletePosRow];
    Cell* front = arr[deletePosRow];
    if(deletePosCol == 0)
    {
        arr[deletePosRow] = arr[deletePosRow]->next;
        delete tmp;
    }
    else
    {
        for (int i = 0; i < deletePosCol; i++)
        {
            front = tmp;
            tmp = tmp->next;
        }
        front->next = tmp->next;
        delete tmp;
    }
}

void deallocateCell(Cell**& arr, int row)
{
    // Deallocating memory for linkedlist
    for (int i = 0; i < row; i++)
    {
        Cell* current = arr[i];
        while (current != nullptr)
        {
            Cell* temp = current;
            current = current->next;
            delete temp;
        }
    }
    delete[] arr;
    arr = nullptr;
}

Cell** transferBoardToLinkedList(int** board, int row, int col)
{
    // Transfer board data into Linkedlist
    Cell** arr = new Cell*[row];
    for (int i = 0; i < row; i++)
    {
        arr[i] = nullptr;
        for (int j = 0; j < col; j++)
        {
            Cell* p = new Cell;
            p->data = board[i + 1][j + 1]; // Bcs board actual index start at (1, 1)
            p->next = nullptr;
            pushCell(arr[i], p);
        }
    }
    return arr;
}

void transferLinkedlistToBoard(Cell** arr, int** &board, int row, int col)
{
    // Transfer Linkedlist data to board
    for (int i = 1; i <= row; i++)
    {
        Cell* tmp = arr[i - 1];
        for (int j = 1; j <= col; j++)
        {
            if (tmp != NULL)
            {
                board[i][j] = tmp->data;
                tmp = tmp->next;
            }
            else
            {
                board[i][j] = 0;
            }
        }
    }
}

void removePokemonHard(int** &board, int deletePosRow, int deletePosCol)
{
    // Remove a pokemon on a pointer matrix using linkedlist allowing it to slide left
    int gameboardRow = 5;
    int gameBoardCol = 8;
    Cell** pokemonLL = transferBoardToLinkedList(board, gameboardRow, gameBoardCol);
    removeCellLocation(pokemonLL, deletePosRow - 1, deletePosCol - 1); // Bcs board location differ from Linkedlist location
    transferLinkedlistToBoard(pokemonLL, board, gameboardRow, gameBoardCol);
    deallocateCell(pokemonLL, gameboardRow);
}
