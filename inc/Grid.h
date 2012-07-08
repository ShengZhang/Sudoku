#ifndef GRID_H
#define GRID_H

#include "common.h"
#include <map>
#include <list>
#include <stack>

class Point;
#define N 9

/**
 * @class
 * Grid class, which is defined as 9*9 array for 
 * the basic operation of Sudoku.
 */
class Grid
{
public:
    Grid(void);
    ~Grid(void);
    static int CELLS[9][9];
    enum BLOCK {
        UNKNOWN = -1,
        B1 = 1,
        B2 = 2,
        B3 = 3,
        B4 = 4,
        B5 = 5,
        B6 = 6,
        B7 = 7,
        B8 = 8,
        B9 = 9
    };

    Grid::BLOCK getCellBlock(int x, int y) const;
    void getStartPointOfBlock(BLOCK block, Point& pt) const;

    bool getCellAvailableValues(Point& pt, list<int>& values) const;
    bool getCellAvailableValues(int x, int y, list<int>& values) const;
    void updateCellAvailableValues(Point* pt, int value);
    Point* getCellWithMinimumAvailableValues() const;
    void setCellValue(Point *pt, int value);
    void setCellValue(Point* pt);

    void initCellAvailableValues();
    bool isEnd();
    void print();
private:
    void clearMap();

    map<Point*, list<int>> m_cellAvailableValues;
};

class Point
{
    public:
        Point(void){};
        Point(int x, int y);
        Point(Point& point);
        ~Point(void);

        bool operator < ( const Point& rhs) const;
        bool operator == (const Point& rhs) const;
        Point& operator = (const Point& rhs);

        int x;
        int y;
};

namespace Helper
{
    void static print(wstring& message, Point* point, int value);
    void static print(wstring& message, int x, int y, int value);
    void static print(wstring& message, Point* point, list<int> values);
    void static print(wstring& message, int x, int y, list<int> values);
};

#endif // GRID_H
