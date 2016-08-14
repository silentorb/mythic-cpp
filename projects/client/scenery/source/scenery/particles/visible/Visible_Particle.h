#pragma once

#include "commoner/dllexport.h"
#include "glm/vec4.hpp"
#include "scenery/particles/Point_Emitter_Bridge.h"
#include <substance/Particle.h>

using namespace glm;

namespace scenery {

  class MYTHIC_EXPORT Visible_Particle {
      float size = 1;
      vec4 color = vec4(1, 1, 1, 1);
      Particle_Point_Delegate *animator = nullptr;

  protected:
      Visible_Particle() :
        color(vec4(1, 1, 1, 1)), size(1) { }

      Visible_Particle(float size, const vec4 &color) :
        color(color), size(size) { }

  public:

      const vec4 &get_color() const {
        return color;
      }

      void set_color(const vec4 &color) {
        Visible_Particle::color = color;
      }

      float get_size() const {
        return size;
      }

      void set_size(float size) {
        Visible_Particle::size = size;
      }

      const vec3 get_position() {
        return get_particle()->get_position();
      }

      void update(float delta) {
        if (animator) {
          (*animator)(*this);
        }
      }

      float get_life() const {
        return get_particle()->get_life();
      }

      virtual const Particle *get_particle() const = 0;
      void set_animator(Particle_Point_Delegate &animator) {
        this->animator = &animator;
      }
  };

}