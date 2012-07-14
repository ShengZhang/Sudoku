//#include "StdAfx.h"
#include "trace.h"
#include "Grid.h"
#include <sstream>
#include <cstdio>


// Grid class implementation
//
/*int Grid::CELLS[9][9] = {
        {4,0,5,9,0,1,3,2,7},//{9,0,8,0,3,1,0,0,0}, //{9,0,5,0,8,1,0,0,0}, 
        {1,0,0,0,0,0,0,9,0},//{0,0,0,0,2,0,5,0,0}, //{0,0,0,0,3,0,8,0,0}, 
        {0,6,7,0,4,0,0,0,8},//{5,0,0,0,9,0,0,4,0}, //{8,0,0,0,2,0,0,7,0}, 
        {0,2,4,0,3,5,0,0,9},//{0,0,0,8,0,0,0,0,5}, //{0,0,0,8,0,0,0,0,4}, 
        {0,5,0,7,8,9,0,4,0},//{8,3,2,0,0,0,1,7,4}, //{3,2,9,0,0,0,5,8,7}, 
        {6,0,0,4,1,0,8,5,0},//{1,0,0,0,0,7,0,0,0}, //{1,0,0,0,0,7,0,0,0}, 
        {5,0,0,0,2,0,9,8,0},//{0,8,0,0,5,0,0,0,3}, //{0,5,0,0,1,0,0,0,6}, 
        {0,1,0,0,0,0,0,0,5},//{0,0,7,0,8,0,0,0,0}, //{0,0,4,0,7,0,0,0,0}, 
        {7,9,8,1,0,6,4,0,2}//{0,0,0,4,7,0,6,0,2}//{0,0,0,5,4,0,3,0,2}
    };
	*/
int Grid::CELLS[9][9] = {
    };

Grid::Grid(void)
{
   
}


Grid::~Grid(void)
{
    this->clearMap();
}

void Grid::initCellAvailableValues()
{
    this->clearMap();

    for(int i = 0; i < N; ++i)
        for(int j = 0; j < N; ++j)
        {
            if(0 == this->CELLS[i][j])
            {
                list<int> values;
                this->getCellAvailableValues(i,j, values);

                Point* point = new Point(i, j);
                this->m_cellAvailableValues.insert(make_pair(point, values));
        
                wstring message = L"Init Available Point values";
                Helper::print(message, point, values);
            }
        }
}

bool Grid::getCellAvailableValues(Point& pt, list<int>& values) const
{
    return this->getCellAvailableValues(pt.x, pt.y, values);
}

bool Grid::getCellAvailableValues(int x, int y, list<int>& values) const
{
    /** We should fullfil 3 conditions for the value in this cell:
     * 1. The value can't duplicated with the values in row across this cell.
     * 2. The value can't duplicated with the values in column across this cell.
     * 3. The value can't duplicated with the values in the block the cell belongs to.
     */
    int myints[]= {1,2,3,4,5,6,7,8,9};
    list<int> valuesList(myints,myints + sizeof(myints) / sizeof(int));
    for(int i = 0; i < N; ++i)
    {
        int a = Grid::CELLS[x][i];
        int b = Grid::CELLS[i][y];
        valuesList.remove(a);
        valuesList.remove(b);
    }

    BLOCK block = this->getCellBlock(x, y);
    Point point;
    this->getStartPointOfBlock(block, point);
    int x1 = point.x;
    int y1 = point.y;

    for(int j = x1; j < x1 + N/3; ++j)
    {
        for(int k = y1; k < y1 + N/3; ++k)
        {
            valuesList.remove(Grid::CELLS[j][k]);
        }
    }

    values = valuesList;
    if(values.size() > 0)
        return true;
    else 
        return false;
}

Grid::BLOCK Grid::getCellBlock(int x, int y) const
{
    BLOCK type = Grid::UNKNOWN;
    if(x < 3 && y < 3)
        type = Grid::B1;
    else if(x >= 3 && x < 6 && y < 3)
        type = Grid::B2;
    else if(x >= 6 && y < 3)
        type = Grid::B3;
    else if(x < 3 && y >= 3 && y < 6)
        type = Grid::B4;
    else if(x >= 3 && x < 6 && y >= 3 && y < 6)
        type = Grid::B5;
    else if(x >= 6 && y >= 3 && y < 6)
        type = Grid::B6;
    else if(x < 3 && y >= 6)
        type = Grid::B7;
    else if(x >= 3 && x < 6 && y >= 6)
        type = Grid::B8;
    else if(x >= 6 && y >= 6)
        type = Grid::B9;
    else
        assert(false);

    return type;
}

void Grid::getStartPointOfBlock(BLOCK block, Point& pt) const
{
    switch(block){
    case Grid::B1:
        pt.x = 0;
        pt.y = 0;
        break;
    case Grid::B2:
        pt.x = 3;
        pt.y = 0;
        break;
    case Grid::B3:
        pt.x = 6;
        pt.y = 0;
        break;
    case Grid::B4:
        pt.x = 0;
        pt.y = 3;
        break;
    case Grid::B5:
        pt.x = 3;
        pt.y = 3;
        break;
    case Grid::B6:
        pt.x = 6;
        pt.y = 3;
        break;
    case Grid::B7:
        pt.x = 0;
        pt.y = 6;
        break;
    case Grid::B8:
        pt.x = 3;
        pt.y = 6;
        break;
    case Grid::B9:
        pt.x = 6;
        pt.y = 6;
        break;
    default:
        assert(false);
    };
}

void Grid::print()
{
    cout<<"*****Begin*****"<<endl;
    for(int i = 0; i < N; ++i)
    {
        for(int j = 0; j < N; ++j)
        {
            cout<<Grid::CELLS[j][i]<<' ';
        }

        cout<<'\n'<<endl;
    }
    cout<<"*****End*****"<<endl;
}

void Grid::clearMap()
{
    if(this->m_cellAvailableValues.size() > 0)
        this->m_cellAvailableValues.clear();
}

bool Grid::isEnd()
{
    map<Point*, list<int>>::iterator iter;
    for(iter = Grid::m_cellAvailableValues.begin(); iter != Grid::m_cellAvailableValues.end(); ++iter)
    {
        list<int> values = (*iter).second;
        int temp = (int) values.size();
        if(temp > 0)
        {
            return false;
        }
    }

    return true;
}

Point* Grid::getCellWithMinimumAvailableValues() const
{
    Point* pPoint = NULL;
    int valueLength = 10;
    map<Point*, list<int>>::const_iterator iter;
    for(iter = Grid::m_cellAvailableValues.begin(); iter != Grid::m_cellAvailableValues.end(); ++iter)
    {
        list<int> values = (*iter).second;
        int temp = (int) values.size();
        if(temp < valueLength && temp > 0)
        {
            pPoint = (*iter).first;
            valueLength = values.size();
        }
    }

    return pPoint;
}

void Grid::setCellValue(Point* pt, int value)
{

    Grid::CELLS[pt->x][pt->y] = value;

    // TODO: maitein a list to record changed point

    // update related cells available values
    this->updateCellAvailableValues(pt, value);

    wstring message = L"Changed Point";
    Helper::print(message, pt, value);
}

void Grid::setCellValue(Point* pt)
{
    map<Point*, list<int>>::iterator it = this->m_cellAvailableValues.find(pt);
    list<int> values = (*it).second;
    int value = values.front();
    this->setCellValue(pt, value);
}

void Grid::updateCellAvailableValues(Point* pt, int value)
{
    int x = pt->x;
    int y = pt->y;

    // remove current cell's available values.
    this->m_cellAvailableValues[pt].clear();

    // Get the block that current point belongs to.
    BLOCK block = this->getCellBlock(x, y);
    Point point;
    this->getStartPointOfBlock(block, point);
    int x1 = point.x;
    int y1 = point.y;

    map<Point*, list<int>>::iterator iter;
    // remove the value from related column, row, and related block.
     for(iter = Grid::m_cellAvailableValues.begin(); iter != Grid::m_cellAvailableValues.end(); ++iter)
    {
        Point* pPoint = (*iter).first;
        if(x == pPoint->x || y == pPoint->y ||
            (pPoint->x >= x1 && pPoint->x < (x1 + N/3) && pPoint->y >= y1 && pPoint->y < (y1 + N/3)))
        {
            (*iter).second.remove(value);

            wstring message = L"Updated Available Point values";
            Helper::print(message, pPoint, (*iter).second);
        }
    }
}

//@class Point
// 
Point::Point(int x, int y)
{
    this->x = x;
    this->y = y;
}

Point::Point(Point &point)
{
    this->x = point.x;
    this->y = point.y;
}

bool Point::operator < ( const Point& rhs) const
{
    return (this->x < rhs.x);
}

bool Point::operator == (const Point& rhs) const
{
    return (this->x == rhs.x) && (this->y == rhs.y);
}

Point& Point::operator = (const Point& rhs) 
{
    this->x = rhs.x;
    this->y = rhs.y;

    return *this;
}

Point::~Point(void)
{
}

//@class Helper
//
void static Helper::print(wstring& message, Point* point, int value)
{
    Helper::print(message, point->x, point->y, value);
}

void static Helper::print(wstring& message, int x, int y, int value)
{
    wstringstream s;
    s << x;
    s << y;
    wstring str = s.str();
    wstringstream k;
    k << value;
    wstring strk = k.str();
    message.append(L": ").append(str).append(L"--").append(strk).append(L"\n");
#ifdef _DEBUG
    TRACE((TCHAR *)message.c_str());
#endif
}

void static Helper::print(wstring& message, Point* point, list<int> values)
{
    Helper::print(message, point->x, point->y, values);
}

void static Helper::print(wstring& message, int x, int y, list<int> values)
{
    wstringstream s;
    s << x;
    s << y;
    wstring str = s.str();
    wstringstream k;
    list<int>::iterator it;
    for(it = values.begin(); it != values.end(); ++it)
    {
        k << (*it);
    }

    wstring valuesk = k.str();
    message.append(L": ").append(str).append(L"--").append(valuesk).append(L"\n");
#ifdef _DEBUG
    TRACE((TCHAR *)message.c_str());
#endif
}