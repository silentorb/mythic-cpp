#pragma once

#include "dllexport.h"
#include <functional>
#include "bloom/bloom_export.h"

namespace songbird {
  template <typename T>
  class Song;
}

using namespace std;

namespace bloom {
  class Flower_Old;

  typedef function<void(Flower_Old *flower)> Flower_Delegate;

  namespace Events {
    BLOOM_EXPORT extern const songbird::Song<Flower_Delegate> activate;
    BLOOM_EXPORT extern const songbird::Song<Flower_Delegate> drag;
    BLOOM_EXPORT extern const songbird::Song<Flower_Delegate> close;
    BLOOM_EXPORT extern const songbird::Song<Flower_Delegate> cancel;
  };
}