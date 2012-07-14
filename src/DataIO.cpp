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
	ifstream file("input.txt");
	if (file.is_open())
	{

		std::stringstream buffer;
		buffer << file.rdbuf();
		string contents(buffer.str());

		vector<string> data = DataIO::split(contents, ',');

		// Init Grid::CELLS
		for(int i = 0; i < (int)data.size(); ++i)
		{
			string item = data[i];
			stringstream str(item);
			int value;
			str >> value;
			/* Lets not forget to error checking */
			if (!str)
			{
				 // The conversion failed.
				 // Need to do something here.
				 // Maybe throw an exception
			}

			int y = i%N;
			int x = i/N;
			Grid::CELLS[x][y] = value;
		}
	}
}

vector<string>& DataIO::split(const string &s, char delim, vector<string> &elems) 
{
    stringstream ss(s);
    string item;
    while(getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}


vector<std::string> DataIO::split(const string &s, char delim) 
{
    vector<string> elems;
    return split(s, delim, elems);
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