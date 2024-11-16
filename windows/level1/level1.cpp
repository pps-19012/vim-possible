#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <conio.h>
#include <tuple>
#include <windows.h>

const int GRID_SIZE = 25;

void initializeGrid(char grid[GRID_SIZE][GRID_SIZE], int &playerX, int &playerY);
void updateGrid(char prevGrid[GRID_SIZE][GRID_SIZE], char newGrid[GRID_SIZE][GRID_SIZE]);
void displayGrid(char grid[GRID_SIZE][GRID_SIZE]);
void clearConsole();
void getCursorPosition();
void setCursorAppearance(bool visible);
void placeRandomTarget(char[GRID_SIZE][GRID_SIZE], int &playerX, int &playerY, int &targetX, int &targetY);
bool movePlayer(char grid[GRID_SIZE][GRID_SIZE], int &playerX, int &playerY, char direction);

int main()
{
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

    clearConsole();
    // getCursorPosition();
    setCursorAppearance(false);
    displayGrid(newGrid);

    while (targetsReached < targetsToReach)
    {
        char input = _getch();

        if (movePlayer(newGrid, playerX, playerY, input))
        {
            if (playerX == targetX && playerY == targetY)
            {
                targetsReached++;
                placeRandomTarget(newGrid, playerX, playerY, targetX, targetY);
            }
        }

        updateGrid(prevGrid, newGrid);
    }

    newGrid[targetY][targetX] = '.';
    updateGrid(prevGrid, newGrid);
    std::cout << "Level Complete!";
    return 0;
}

void displayGrid(char grid[GRID_SIZE][GRID_SIZE])
{
    for (int i = 0; i < GRID_SIZE; i++)
    {
        for (int j = 0; j < GRID_SIZE; j++)
        {
            // std::cout << grid[i][j] << ' ';
            std::cout << grid[i][j];
        }
        std::cout << '\n';
    }
}

void clearConsole()
{
    static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD topLeft = {0, 0};
    std::cout.flush();
    SetConsoleCursorPosition(hOut, topLeft);
}

bool movePlayer(char grid[GRID_SIZE][GRID_SIZE], int &playerX, int &playerY, char direction)
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

void getCursorPosition()
{
    int x, y;
    static const HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (GetConsoleScreenBufferInfo(hConsole, &csbi))
    {
        x = csbi.dwCursorPosition.X;
        y = csbi.dwCursorPosition.Y;
    }
    std::cout << "Current cursor position: (" << x << ", " << y << ")\n";
}

void updateGrid(char prevGrid[GRID_SIZE][GRID_SIZE], char newGrid[GRID_SIZE][GRID_SIZE])
{
    for (int i = 0; i < GRID_SIZE; i++)
    {
        for (int j = 0; j < GRID_SIZE; j++)
        {
            if (newGrid[i][j] == prevGrid[i][j])
            {
                continue;
            }
            setCursorPosition(j, i);
            std::cout << newGrid[i][j];
        }
    }
    std::cout.flush();
    std::memcpy((char *)prevGrid, (char const *)newGrid, GRID_SIZE * GRID_SIZE);
}