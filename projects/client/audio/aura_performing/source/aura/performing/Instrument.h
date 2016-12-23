#pragma once

#include <memory>

namespace aura {
  namespace performing {

    template<typename Sound_Type, typename Event_Type>
    class Instrument {
    public:
        virtual std::unique_ptr<Sound_Type> create_sound(const Event_Type &event) = 0;
        virtual ~Instrument() {}
    };
  }
}