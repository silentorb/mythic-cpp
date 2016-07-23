#ifdef _MSC_VER
#ifdef AURA_LIB
#define AURA_EXPORT __declspec(dllexport)
#else
#define AURA_EXPORT __declspec(dllimport)
#endif
#else
#define AURA_EXPORT
#endif
