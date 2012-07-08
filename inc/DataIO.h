#ifndef DATAIO_H
#define DATAIO_H

#include "common.h"

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
};
#endif // DATAIO_H
