#pragma once

#include "main.h"
#include "cell.h"

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

bool isWinning(Cell *cells, SymbolSign c, int i)
{
    // Diagonal right
    if (cells[0].getSymbol() == c
        && cells[4].getSymbol() == c
        && cells[8].getSymbol() == c)
        return true;

    // Diagonal left
    if (cells[2].getSymbol() == c
        && cells[4].getSymbol() == c
        && cells[6].getSymbol() == c)
        return true;

    // Vertical
    if (cells[i].getSymbol() == c
        && cells[(i + 3) % 9].getSymbol() == c
        && cells[(i + 6) % 9].getSymbol() == c)
        return true;

    // Horizontal
    // Get first index of the row
    int row = floor(i / 3) * 3;
    if (cells[row].getSymbol() == c
        && cells[row + 1].getSymbol() == c
        && cells[row + 2].getSymbol() == c)
        return true;

    return false;
}

bool hasEmptyGrid(Cell *cells, int &pos)
{
    int tPos = pos;
    while (tPos < (pos + 3))
    {
        if (cells[winPatterns[tPos]].getSymbol() == SYMBOL_SIGN_EMPTY)
        {
            pos = tPos;
            return true;
        }

        tPos = (tPos + 1) % 24;
    }

    return false;
}

void solve(Cell *cells, SymbolSign sym, SymbolSign oppSym, int &pos)
{
    // CPU win algorithm
    int nextPos = -1;
    int defPos = -1;
    int offPos = -1;

    int offScore = 0;
    int defScore = 0;

    for (int i = 0; i < 24; i += 3)
    {
        int tempScore = 0;

        // Empty col checking
        tempScore = (cells[winPatterns[i]].getSymbol() == SYMBOL_SIGN_EMPTY) ? tempScore + 1 : tempScore;
        tempScore = (cells[winPatterns[i + 1]].getSymbol() == SYMBOL_SIGN_EMPTY) ? tempScore + 1 : tempScore;
        tempScore = (cells[winPatterns[i + 2]].getSymbol() == SYMBOL_SIGN_EMPTY) ? tempScore + 1 : tempScore;

        if (tempScore <= 0)
            continue;

        tempScore = 0;

        // Offensive checking
        tempScore = (cells[winPatterns[i]].getSymbol() == sym) ? tempScore + 1 : tempScore;
        tempScore = (cells[winPatterns[i + 1]].getSymbol() == sym) ? tempScore + 1 : tempScore;
        tempScore = (cells[winPatterns[i + 2]].getSymbol() == sym) ? tempScore + 1 : tempScore;

        if (tempScore >= 1 && offScore < 2)
        {
            offScore = tempScore;
            offPos = i;
        }

        tempScore = 0;

        // Deffense checking
        tempScore = (cells[winPatterns[i]].getSymbol() == oppSym) ? tempScore + 1 : tempScore;
        tempScore = (cells[winPatterns[i + 1]].getSymbol() == oppSym) ? tempScore + 1 : tempScore;
        tempScore = (cells[winPatterns[i + 2]].getSymbol() == oppSym) ? tempScore + 1 : tempScore;

        if (tempScore == 2)
        {
            defScore = tempScore;
            defPos = i;
        }
    }

    if (offScore >= 2 && hasEmptyGrid(cells, offPos))
    {
        nextPos = winPatterns[offPos];
        defScore = 0;
    }

    if (defScore >= 2 && hasEmptyGrid(cells, defPos))
    {
        nextPos = winPatterns[defPos];
    }

    if (nextPos == -1)
    {
        int npos = 4;
        int max = npos + 9;

        while (npos < max)
        {
            if (cells[npos % 9].getSymbol() == SYMBOL_SIGN_EMPTY && (npos % 9) % 2 == 0)
            {
                nextPos = npos % 9;
                break;
            }

            if (cells[npos % 9].getSymbol() == SYMBOL_SIGN_EMPTY)
                nextPos = npos % 9;

            npos++;
        }
    }

    cells[nextPos].insertSymbol(sym);
    pos = nextPos;
}