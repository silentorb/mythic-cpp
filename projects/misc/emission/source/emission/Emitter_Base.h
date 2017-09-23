#pragma once

#include <vector>
#include <memory>

namespace emission {

  template<typename Particle_Type>
  using Particle_Factory = std::function<Particle_Type()>;
  using Empty_Delegate = std::function<void()>;

  template<typename Particle_Type>
  class Emitter_Base {
  protected:
      float rate = 0; // particles per second
      Empty_Delegate factory;

      virtual void generate(float delta) = 0;

  public:
      Emitter_Base(const Empty_Delegate &factory) :
        factory(factory) {}

      void set_rate(float value) {
        rate = value;
      }

      void operator()(float delta);
  };

}