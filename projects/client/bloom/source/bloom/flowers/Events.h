#pragma once

#include "dllexport.h"
#include <functional>

using namespace std;

namespace bloom {
  class Flower;

  typedef function<void(Flower *flower)> Flower_Delegate;

  namespace Events {
    extern songbird::Song<Flower_Delegate> activate;
    extern songbird::Song<Flower_Delegate> close;
    extern songbird::Song<Flower_Delegate> cancel;
  };

}