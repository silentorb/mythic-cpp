#pragma once
#include "debug-macro.h"

/*
 * Unlike the STL assert(), this Assert throws an exception, allowing debuggers to halt execution
 * on the line where the assertion failed.  With some debugging configurations the default assert silently
 * closes the program with no way of seeing the brief console output and knowing what ever happened.
 */

#if COMMONER_DEBUG
inline void Assert(bool expression) {
  if (!expression)
    throw "";
}
#else
#define Assert(x)
#endif