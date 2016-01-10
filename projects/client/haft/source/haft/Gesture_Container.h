#pragma once

#include "Gesture.h"

namespace haft {

  class Gesture_Container {
      virtual Gesture &get_gesture(int index) const = 0;

      virtual void add_gesture(Gesture *gesture) = 0;

      virtual int get_gesture_count() const = 0;
  };

}

