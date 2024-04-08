#pragma once

#include "main.h"

int winPatterns[] = {
    // Horizontal
    0, 1, 2,
    3, 4, 5,
    6, 7, 8,

    // Vertical
    0, 3, 6,
    1, 4, 7,
    2, 5, 8,

    // Diagonal
    0, 4, 8,
    2, 4, 6
};

bool isWinning(const char *cells, char c, int i)
{
    // Diagonal right
    if (cells[0] == c
        && cells[4] == c
        && cells[8] == c)
        return true;

    // Diagonal left
    if (cells[2] == c
        && cells[4] == c
        && cells[6] == c)
        return true;

    // Vertical
    if (cells[i] == c
        && cells[(i + 3) % 9] == c
        && cells[(i + 6) % 9] == c)
        return true;

    // Horizontal
    // Get first index of the row
    int row = floor(i / 3) * 3;
    if (cells[row] == c
        && cells[row + 1] == c
        && cells[row + 2] == c)
        return true;

    return false;
}

bool hasEmptyGrid(const char *cells, int pos)
{
    int tPos = pos;
    while (tPos < (pos + 3))
    {
        if (cells[winPatterns[tPos]] == ' ')
        {
            pos = tPos;
            return true;
        }

        tPos = (tPos + 1) % arrLen(winPatterns);
    }

    return false;
}