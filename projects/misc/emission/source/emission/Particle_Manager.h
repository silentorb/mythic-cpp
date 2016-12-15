#pragma once

#include <vector>
#include <functional>
#include <memory>

namespace emission {

  template<typename Particle_Type>
  using Particle_Updater = std::function<void(Particle_Type &, float delta)>;

  template<typename Particle_Type>
  using Particle_Delegate = std::function<void(Particle_Type &)>;

  template<typename Particle_Type>
  class Particle_Manager {
      std::vector<std::unique_ptr<Particle_Type>> particles;
      Particle_Updater<Particle_Type> updater;
      Particle_Delegate<Particle_Type> on_delete;

  public:

      std::vector<std::unique_ptr<Particle_Type>> &get_particles() {
        return particles;
      }

      void update_particles(float delta) {
//    for (int i = particles.size() - 1; i >= 0; --i) {
//      auto &particle = particles[i];
        if (particles.size() == 0)
          return;

        auto particle = particles.data() + particles.size();
        while (particle != particles.data())
          --particle;
        if (updater)
          updater(*particle->get(), delta);

        if (particle->get()->is_finished()) {
          if (on_delete)
            on_delete(*particle->get());

          particles.erase(particles.begin() + (particle - particles.data()));
        }
      };

      void add_particle(std::unique_ptr<Particle_Type> &particle) {
        particles.push_back(std::move(particle));
      }

      void set_updater(const Particle_Updater<Particle_Type> &value) {
        updater = value;
      }

      void set_on_delete(const Particle_Delegate<Particle_Type> &value) {
        on_delete = value;
      }
  };
}