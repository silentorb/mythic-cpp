#pragma once

#include "Sound.h"
#include <memory>

namespace foley {

  class Library {
  public:
      virtual std::unique_ptr<Sound> get_sound(int id) const = 0;
  };
}