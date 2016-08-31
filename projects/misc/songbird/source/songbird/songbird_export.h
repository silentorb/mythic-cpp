#pragma once

#if defined (_MSC_VER)
#ifdef  SONGBIRD_LIB
#define  SONGBIRD_EXPORT __declspec(dllexport)
#else
#define  SONGBIRD_EXPORT __declspec(dllimport)
#endif
#else
#define  SONGBIRD_EXPORT
#endif