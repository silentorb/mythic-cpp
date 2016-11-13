#pragma once

namespace aura {
  namespace performing {

    template <typename Signal_Type>
    class Sound {
    public:
        virtual Signal_Type update(float delta) = 0;
        virtual bool is_finished() const = 0;
    };
  }
}