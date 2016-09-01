#pragma once

#if defined (_MSC_VER)
#ifdef BLOOM_LIB
#define BLOOM_EXPORT __declspec(dllexport)
#else
#define BLOOM_EXPORT __declspec(dllimport)
#define BLOOM_EXPORT
#endif
#else
#define BLOOM_EXPORT
#endif