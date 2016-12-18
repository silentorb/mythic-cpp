#pragma once

#include <aura/primitives.h>

namespace aura {
  namespace performing {

    template<typename Signal_Type>
    class Sound {
    public:
        virtual ~Sound() {}

        virtual Signal_Type update(float delta) = 0;
        virtual bool is_finished() const = 0;
        virtual Seconds get_duration() const = 0;

        Signal_Type operator()(float delta) {
          return update(delta);
        }
    };
  }
}