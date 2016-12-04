#pragma once

#include <emission/Emitter.h>

namespace aura {
  namespace generation {

    template<typename Signal_Type, typename Sound_Type>
    class Sound_Emitter {
        emission::Emitter<Sound_Type> emitter;

    public:
        Sound_Emitter(const emission::Particle_Factory<Sound_Type> &factory) :
          emitter(factory) {}

        Signal_Type operator()(float delta) {
          emitter(delta);
          Signal_Type result = 0;

          for (auto &particle : emitter.get_particles()) {
            result += particle->update(delta);
          }

          return result;
        }

        void set_rate(int rate){
          emitter.set_rate(rate);
        }
    };
  }
}