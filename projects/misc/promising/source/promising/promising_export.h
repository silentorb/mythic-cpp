#pragma once

#if defined (_MSC_VER)
#ifdef PROMISING_LIB
#define PROMISING_EXPORT __declspec(dllexport)
#else
#define PROMISING_EXPORT __declspec(dllimport)
#endif
#else
#define PROMISING_EXPORT
#endif