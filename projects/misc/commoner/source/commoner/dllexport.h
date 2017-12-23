#pragma once

#define MYTHIC_STRING2(x) #x
#define MYTHIC_STRING(x) MYTHIC_STRING2(x)

#if defined (_MSC_VER)
#if defined(EXPORTING_DLL)
#define MANUAL_SYMBOL_EXPORTING
#define __declspec(dllexport)
#else
//#define __declspec(dllimport)
#define MYTHIC_EXPORT
#endif /* MyLibrary_EXPORTS */
#else /* defined (_WIN32) */
#define MYTHIC_EXPORT
#endif

#include "no_copy.h"