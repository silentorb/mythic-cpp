#pragma once

#include "dllexport.h"
#include <functional>
#include "bloom/bloom_export.h"

using namespace std;


namespace bloom {
  class Flower;

  typedef function<void(Flower *flower)> Flower_Delegate;

  namespace Events {
    BLOOM_EXPORT extern const songbird::Song<Flower_Delegate> activate;
    BLOOM_EXPORT extern const songbird::Song<Flower_Delegate> close;
    BLOOM_EXPORT extern const songbird::Song<Flower_Delegate> cancel;
  };
}