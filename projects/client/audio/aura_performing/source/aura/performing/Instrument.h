#pragma once

#include <memory>
#include "Sound.h"

namespace aura {
  namespace performing {

    template<typename Sound_Type, typename Event_Type>
    class Instrument {
    public:
        virtual std::unique_ptr<Sound_Type> create_sound(const Event_Type &event) const = 0;
        virtual ~Instrument() {}
    };
  }
}