#ifndef TRACE_H
#define TRACE_H

#include <windows.h>
#ifdef _DEBUG
bool _trace(TCHAR *format, ...);
#define TRACE _trace
#else
#define TRACE false && _trace
#endif

#endif // TRACE_H