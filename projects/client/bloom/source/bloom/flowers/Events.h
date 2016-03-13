#pragma once

#include "dllexport.h"
#include <functional>

using namespace std;

#ifdef MANUAL_SYMBOL_EXPORTING
#ifdef BLOOM_LIB
#define BLOOM_EXPORT __declspec(dllexport)
#else
#define BLOOM_EXPORT __declspec(dllimport)
#endif
#else
#define BLOOM_EXPORT
#endif

namespace bloom {
  class Flower;

  typedef function<void(Flower *flower)> Flower_Delegate;

  namespace Events {
    BLOOM_EXPORT extern const songbird::Song<Flower_Delegate> activate;
    BLOOM_EXPORT extern const songbird::Song<Flower_Delegate> close;
    BLOOM_EXPORT extern const songbird::Song<Flower_Delegate> cancel;
  };
}