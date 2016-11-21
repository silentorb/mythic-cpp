#pragma once

#include <vector>
#include <memory>

namespace emission {

  template<typename Particle_Type>
  using Particle_Factory = std::function<Particle_Type *()>;

  template<typename Particle_Type>
  using Particle_Updater = std::function<void(Particle_Type &, float delta)>;

  template<typename Particle_Type>
  using Particle_Delegate = std::function<void(Particle_Type &)>;

  template<typename Particle_Type>
  class Emitter {
      std::vector<std::unique_ptr<Particle_Type>> particles;
      float rate = 0; // particles per second
      float accumulator = 0;
      Particle_Factory<Particle_Type> factory;
      Particle_Updater<Particle_Type> updater;
      Particle_Delegate<Particle_Type> on_delete;

      void update_particles(float delta);
      void generate(float delta);

  public:
      Emitter(const Particle_Factory<Particle_Type> &factory) :
        factory(factory) {}

      void set_rate(float value) {
        rate = value;
      }

      void operator()(float delta);

      std::vector<std::unique_ptr<Particle_Type>> &get_particles() {
        return particles;
      }

      void set_updater(const Particle_Updater<Particle_Type> &value) {
        updater = value;
      }

      void set_on_delete(const Particle_Delegate<Particle_Type> &value) {
        on_delete = value;
      }
  };

}