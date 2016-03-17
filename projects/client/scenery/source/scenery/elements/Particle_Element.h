#pragma once

#include <substance/Particle.h>
#include "dllexport.h"
#include "Group.h"

using namespace substance;

namespace scenery {

  class Particle_Element : public scenery::Group {
      Particle &particle;

  public:
      Particle_Element(Particle &particle, Parent *parent) : particle(particle), scenery::Group(parent) { }

      Particle &get_particle() const {
        return particle;
      }

//      virtual void update(float delta) override {
//				auto absolute_position = vec3(get_transform() * vec4(vec3(0), 1));
//				set_position(vec3(0));
//				//set_position(particle.get_position());
//      }

      virtual mat4 get_transform() override;


  };
}