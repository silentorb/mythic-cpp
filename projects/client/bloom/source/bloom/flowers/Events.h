#pragma once

#include "dllexport.h"
#include <functional>

using namespace std;

#ifdef MANUAL_SYMBOL_EXPORTING
#ifdef BLOOM_LIB
#define BLOOM_EXPORT __declspec(dllexport) extern
#else
#define BLOOM_EXPORT __declspec(dllimport) extern
#endif
#else
#define BLOOM_EXPORT extern
#endif

namespace bloom {
  class Flower;

  typedef function<void(Flower *flower)> Flower_Delegate;

  namespace Events {
    BLOOM_EXPORT const songbird::Song<Flower_Delegate> activate;
    BLOOM_EXPORT const songbird::Song<Flower_Delegate> close;
    BLOOM_EXPORT const songbird::Song<Flower_Delegate> cancel;
  };
}