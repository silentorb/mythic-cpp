#pragma once

#include "dllexport.h"
#include <functional>

using namespace std;

namespace bloom {

  enum class Events {
      activate,
      close,
      cancel,
  };

  class Flower;

  typedef function<void(Flower *flower)> Flower_Delegate;

  struct MYTHIC_EXPORT Listener {
      Events type;
      Flower_Delegate action;
  };
}