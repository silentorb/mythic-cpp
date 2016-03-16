#pragma once

#ifdef MANUAL_SYMBOL_EXPORTING
#ifdef BLOOM_LIB
#define BLOOM_EXPORT __declspec(dllexport)
#else
#define BLOOM_EXPORT __declspec(dllimport)
#endif
#else
#define BLOOM_EXPORT
#endif