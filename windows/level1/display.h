#ifndef DISPLAY_H
#define DISPLAY_H

#include <windows.h>

const int GRID_SIZE = 25;

void clearConsole();
void setCursorAppearance(bool visible);
void setCursorPosition(int x, int y);
void displayGrid(char grid[GRID_SIZE][GRID_SIZE]);
void updateGrid(char prevGrid[GRID_SIZE][GRID_SIZE], char newGrid[GRID_SIZE][GRID_SIZE], int yOffset, int xOffset);
void getCursorPosition(int &x, int &y);
void levelComplete(int y, int x);

#endif
