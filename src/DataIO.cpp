#include "DataIO.h"
#include <fstream>
#include <sstream>
#include "grid.h"

DataIO::DataIO(void)
{
}

DataIO::~DataIO(void)
{
}

void DataIO::read()
{

}

bool DataIO::write( wstring wsFileName)
{
    DataIO::write((wstring)L"*****Begin*****\n", wsFileName);

    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < N; j++)
        {
            DataIO::write(Grid::CELLS[j][i], wsFileName);
            DataIO::write((wstring) L" ", wsFileName);
        }
        
        DataIO::write((wstring) L"\n", wsFileName);
    }

    DataIO::write((wstring)L"*****End*****\n", wsFileName);
    return true;
}

bool DataIO::write(int value, wstring wsFileName)
{
    wstringstream stream;
    stream << value;
    wstring str = stream.str(); 
    return DataIO::write(str, wsFileName);
}


bool DataIO::write(wstring str, wstring wsFileName)
{
     // TODO: Check if the file is exist or not.
    wofstream writeFile;
    writeFile.open(wsFileName, ios_base::out | ios_base::app);
    if(!writeFile)
    {
        writeFile = wofstream(wsFileName, ios_base::out | ios_base::app);
    }

    if(!writeFile.is_open())
        return false;

    writeFile.write(str.c_str(), (long)str.size());
    writeFile.flush();

    if(writeFile.good())
    {
        writeFile.close();
        return true;
    }
    else
    {
        writeFile.close();
        return false;
    }    
}