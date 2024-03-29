// Sudoku.cpp : Defines the entry point for the console application.
//

#include <stdio.h>
#include <tchar.h>
#include "grid.h"
#include "DataIO.h"

int _tmain(int argc, _TCHAR* argv[])
{
    Grid grid = Grid();
	DataIO::read();
    grid.initCellAvailableValues();
    while(!grid.isEnd())
    {
        Point* minPoint = grid.getCellWithMinimumAvailableValues();
        grid.setCellValue(minPoint);
    }
    //grid.print();
    DataIO::write( L"result.txt");
    return 0;
}

