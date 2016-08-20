#pragma once

#include "commoner/dllexport.h"
#include <functional>
#include "bloom/bloom_export.h"

namespace songbird {
  template<typename T>
  class Song;
}

using namespace std;

namespace bloom {

  class Flower_Old;

  namespace flowers {
    class Flower;
  }

  typedef function<void(Flower_Old *flower)> Flower_Delegate_Old;

  namespace Events {
    BLOOM_EXPORT extern const songbird::Song<Flower_Delegate_Old> activate_old;
    BLOOM_EXPORT extern const songbird::Song<Flower_Delegate_Old> drag_old;
    BLOOM_EXPORT extern const songbird::Song<Flower_Delegate_Old> close_old;
    BLOOM_EXPORT extern const songbird::Song<Flower_Delegate_Old> cancel_old;
  };

  typedef function<void(flowers::Flower *flower)> Flower_Delegate;

  namespace Events {
    BLOOM_EXPORT extern const songbird::Song<Flower_Delegate> activate;
    BLOOM_EXPORT extern const songbird::Song<Flower_Delegate> drag;
    BLOOM_EXPORT extern const songbird::Song<Flower_Delegate> down;
    BLOOM_EXPORT extern const songbird::Song<Flower_Delegate> close;
    BLOOM_EXPORT extern const songbird::Song<Flower_Delegate> cancel;
    BLOOM_EXPORT extern const songbird::Song<Flower_Delegate> changed;
  };
}