#pragma once

#ifdef DEFAULT_EXTERNALS

#define NODE_TEMPLATE
#define POSSIBLE_TEMPLATE
using Default_Externals = DEFAULT_EXTERNALS;

#else

#define NODE_TEMPLATE template<typename Default_Externals>
#define POSSIBLE_TEMPLATE <Default_Externals>

#endif