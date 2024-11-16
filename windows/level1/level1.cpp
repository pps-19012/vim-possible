#include <iostream>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <tuple>

const int GRID_SIZE = 10;

void initializeGrid(char grid[GRID_SIZE][GRID_SIZE], int &playerX, int &playerY);
void displayGrid(char grid[GRID_SIZE][GRID_SIZE]);
void clearScreen();
void moveCursorToTop();
void placeRandomTarget(char[GRID_SIZE][GRID_SIZE], int &playerX, int &playerY, int &targetX, int &targetY);
bool movePlayer(char grid[GRID_SIZE][GRID_SIZE], int &playerX, int &playerY, char direction);

int main()
{
    char grid[GRID_SIZE][GRID_SIZE];

    int playerX = GRID_SIZE / 2;
    int playerY = GRID_SIZE / 2;

    int targetX, targetY;

    initializeGrid(grid, playerX, playerY);

    placeRandomTarget(grid, playerX, playerY, targetX, targetY);

    int targetsReached = 0;
    int targetsToReach = 4;

    while (targetsReached < targetsToReach)
    {
        clearScreen();
        // moveCursorToTop();
        displayGrid(grid);

        char input = _getch();

        if (movePlayer(grid, playerX, playerY, input))
        {
            if (playerX == targetX && playerY == targetY)
            {
                targetsReached++;
                placeRandomTarget(grid, playerX, playerY, targetX, targetY);
            }
        }
    }
    grid[targetY][targetX] = '.';
    // moveCursorToTop();
    clearScreen();
    displayGrid(grid);
    std::cout << "Level Complete!";
    return 0;
}

void displayGrid(char grid[GRID_SIZE][GRID_SIZE])
{
    for (int i = 0; i < GRID_SIZE; i++)
    {
        for (int j = 0; j < GRID_SIZE; j++)
        {
            std::cout << grid[i][j] << ' ';
        }
        std::cout << '\n';
    }
}

void clearScreen()
{
    std::system("CLS");
}

void moveCursorToTop()
{
    // std::cout << "\033H";
    printf("\033[0;0H\033[2J");
}

bool movePlayer(char grid[GRID_SIZE][GRID_SIZE], int &playerX, int &playerY, char direction)
{
    grid[playerY][playerX] = '.';
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
        return false;
    }
    grid[playerY][playerX] = 'P';
    return true;
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