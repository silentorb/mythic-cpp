#pragma once

#include "dllexport.h"
#include <functional>

using namespace std;

namespace bloom {
  class Flower;

  typedef function<void(Flower *flower)> Flower_Delegate;

  namespace Events {
    MYTHIC_EXPORT extern songbird::Song<Flower_Delegate> activate;
    MYTHIC_EXPORT extern songbird::Song<Flower_Delegate> close;
    MYTHIC_EXPORT extern songbird::Song<Flower_Delegate> cancel;
  };

}