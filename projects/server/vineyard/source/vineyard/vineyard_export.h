#pragma once

#if defined (_MSC_VER)
#ifdef VINEYARD_LIB
#define VINEYARD_EXPORT __declspec(dllexport)
#else
#define VINEYARD_EXPORT __declspec(dllimport)
#define VINEYARD_EXPORT
#endif
#else
#define VINEYARD_EXPORT
#endif