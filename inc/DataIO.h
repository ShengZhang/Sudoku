#ifndef DATAIO_H
#define DATAIO_H

#include "common.h"
#include <vector>

/**
 * @class
 */
class DataIO
{
public:
    DataIO(void);
    virtual ~DataIO(void);

    void static read();
    bool static write(wstring str, wstring wsFileName);
    bool static write(int value, wstring wsFileName);
    bool static write( wstring wsFileName);
private:
	static vector<string>&  split(const string &s, char delim, vector<string> &elems);
	static vector<std::string> split(const string &s, char delim);
};
#endif // DATAIO_H
