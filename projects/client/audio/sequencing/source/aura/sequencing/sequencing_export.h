#pragma once

#if defined (_MSC_VER)
#ifdef EXPORTING_DLL
#ifdef SEQUENCING_LIB
#define SEQUENCING_EXPORT __declspec(dllexport)
#else
#define SEQUENCING_EXPORT __declspec(dllimport)
#endif
#else
#define SEQUENCING_EXPORT
#endif
#else
#define SEQUENCING_EXPORT
#endif