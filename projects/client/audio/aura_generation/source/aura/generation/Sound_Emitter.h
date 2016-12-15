#pragma once

#include <emission/Random_Emitter.h>
#include <emission/Particle_Manager.h>

namespace aura {
  namespace generation {

    template<typename Signal_Type, typename Sound_Type>
    class Sound_Emitter {
        emission::Random_Emitter<Sound_Type> emitter;
        emission::Particle_Manager<Sound_Type> particle_manager;

    public:
        Sound_Emitter(const emission::Particle_Factory<Sound_Type*> &factory, randomly::Dice &dice) :
          emitter([this, factory]() {
            auto particle = std::unique_ptr<Sound_Type>(factory());
            particle_manager.add_particle(particle);
          }, dice) {}

        Signal_Type operator()(float delta) {
          emitter(delta);
          Signal_Type result = 0;

          for (auto &particle : particle_manager.get_particles()) {
            result += particle->update(delta);
          }

          return result;
        }

        void set_rate(int rate) {
          emitter.set_rate(rate);
        }
    };
  }
}