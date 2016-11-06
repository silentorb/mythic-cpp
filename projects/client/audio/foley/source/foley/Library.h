#pragma once

#include "Sound_Data.h"
#include <memory>

namespace foley {

  class Library {
  public:
      virtual std::unique_ptr<Sound_Data> get_sound(int id) const = 0;
  };
}