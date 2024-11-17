#include "Display.h"
#include <iostream>
#include <cstring>
#include <windows.h>

void clearConsole()
{
    static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD topLeft = {0, 0};
    std::cout.flush();
    SetConsoleCursorPosition(hOut, topLeft);
}

void setCursorAppearance(bool visible)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;

    GetConsoleCursorInfo(hConsole, &cursorInfo);

    cursorInfo.bVisible = visible;

    SetConsoleCursorInfo(hConsole, &cursorInfo);
}

void setCursorPosition(int x, int y)
{
    static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    std::cout.flush();
    COORD coord = {(SHORT)x, (SHORT)y};
    SetConsoleCursorPosition(hOut, coord);
}

void getCursorPosition(int &x, int &y)
{
    static const HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (GetConsoleScreenBufferInfo(hConsole, &csbi))
    {
        x = csbi.dwCursorPosition.X;
        y = csbi.dwCursorPosition.Y;
    }
    // std::cout << "X: " << x << " , Y: " << y << '\n';
}

void displayGrid(char grid[GRID_SIZE][GRID_SIZE], int yOffset, int xOffset)
{
    setCursorPosition(yOffset, xOffset);
    for (int i = 0; i < GRID_SIZE; i++)
    {
        for (int j = 0; j < GRID_SIZE; j++)
        {
            std::cout << grid[i][j];
            // std::cout << grid[i][j] << ' ';
        }
        std::cout << '\n';
    }
}

void updateGrid(char prevGrid[GRID_SIZE][GRID_SIZE], char newGrid[GRID_SIZE][GRID_SIZE], int yOffset, int xOffset)
{
    setCursorPosition(yOffset, xOffset);
    for (int i = 0; i < GRID_SIZE; i++)
    {
        for (int j = 0; j < GRID_SIZE; j++)
        {
            if (newGrid[i][j] == prevGrid[i][j])
            {
                continue;
            }
            setCursorPosition(j + yOffset, i + xOffset);
            std::cout << newGrid[i][j];
        }
    }
    std::cout.flush();
    std::memcpy((char *)prevGrid, (char const *)newGrid, GRID_SIZE * GRID_SIZE);
}

void levelComplete(int y, int x)
{
    setCursorPosition(y, x);
    std::cout << "Level Complete!";
    setCursorAppearance(true);
}