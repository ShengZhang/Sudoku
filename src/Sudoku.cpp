// Sudoku.cpp : Defines the entry point for the console application.
//

#include <stdio.h>
#include <tchar.h>
#include "grid.h"

int _tmain(int argc, _TCHAR* argv[])
{
    Grid grid = Grid();
    grid.initCellAvailableValues();
    while(!grid.isEnd())
    {
        Point* minPoint = grid.getCellWithMinimumAvailableValues();
        grid.setCellValue(minPoint);

        grid.print();
    }

    return 0;
}

