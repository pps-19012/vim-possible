#include <iostream>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <windows.h>
#include "display.h"

void initializeGrid(char grid[GRID_SIZE][GRID_SIZE], int &playerX, int &playerY);
void placeRandomTarget(char[GRID_SIZE][GRID_SIZE], int &playerX, int &playerY, int &targetX, int &targetY);
bool movePlayer(char grid[GRID_SIZE][GRID_SIZE], int &playerX, int &playerY, char direction, int yOffset, int xOffset);

bool movePlayer(char grid[GRID_SIZE][GRID_SIZE], int &playerX, int &playerY, char direction, int yOffset, int xOffset)
{
    bool move = true;
    int originalX = playerX;
    int originalY = playerY;
    switch (direction)
    {
    case 'h':
        if (playerX > 0)
        {
            playerX--;
        }
        break;
    case 'j':
        if (playerY < GRID_SIZE - 1)
        {
            playerY++;
        }
        break;
    case 'k':
        if (playerY > 0)
        {
            playerY--;
        }
        break;
    case 'l':
        if (playerX < GRID_SIZE - 1)
        {
            playerX++;
        }
        break;
    default:
        move = false;
    }
    if (move)
    {
        grid[originalY][originalX] = '.';
        grid[playerY][playerX] = 'P';
        return true;
    }
    return false;
}

void initializeGrid(char grid[GRID_SIZE][GRID_SIZE], int &playerX, int &playerY)
{
    for (int i = 0; i < GRID_SIZE; i++)
    {
        for (int j = 0; j < GRID_SIZE; j++)
        {
            grid[i][j] = '.';
        }
    }

    grid[playerY][playerX] = 'P';
}

void placeRandomTarget(char grid[GRID_SIZE][GRID_SIZE], int &playerX, int &playerY, int &targetX, int &targetY)
{
    std::srand(std::time(nullptr));

    targetX = std::rand() % GRID_SIZE;
    targetY = std::rand() % GRID_SIZE;

    while (targetX == playerX && targetY == playerY)
    {
        targetX = std::rand() % GRID_SIZE;
        targetY = std::rand() % GRID_SIZE;
    }
    grid[targetY][targetX] = 'X';
}

int main()
{
    std::cout << "Level-1: Use h(left), j(up), k(down), and l(right) to reach X." << '\n';

    int yOffset, xOffset;
    getCursorPosition(yOffset, xOffset);

    char prevGrid[GRID_SIZE][GRID_SIZE];
    char newGrid[GRID_SIZE][GRID_SIZE];

    int playerX = GRID_SIZE / 2;
    int playerY = GRID_SIZE / 2;

    int targetX, targetY;

    initializeGrid(prevGrid, playerX, playerY);
    initializeGrid(newGrid, playerX, playerY);

    placeRandomTarget(newGrid, playerX, playerY, targetX, targetY);

    int targetsReached = 0;
    int targetsToReach = 4;

    setCursorAppearance(false);
    displayGrid(newGrid, yOffset, xOffset);

    while (targetsReached < targetsToReach)
    {
        char input = _getch();

        if (movePlayer(newGrid, playerX, playerY, input, yOffset, xOffset))
        {
            if (playerX == targetX && playerY == targetY)
            {
                targetsReached++;
                placeRandomTarget(newGrid, playerX, playerY, targetX, targetY);
            }
        }

        updateGrid(prevGrid, newGrid, yOffset, xOffset);
    }

    newGrid[targetY][targetX] = '.';
    updateGrid(prevGrid, newGrid, yOffset, xOffset);
    levelComplete(yOffset, xOffset + GRID_SIZE);
    return 0;
}