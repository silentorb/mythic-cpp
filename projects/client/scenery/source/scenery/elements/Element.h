#pragma once

#include <glm/gtc/quaternion.hpp>
#include "dllexport.h"

#include "lookinglass/Renderable.h"
#include "glm/glm.hpp"

using namespace lookinglass;
using namespace glm;

namespace scenery {
  class Group;

  class MYTHIC_EXPORT Element : public Renderable, no_copy {
  private:
      vec3 position;
      quat orientation;
      vec3 scale;
      Group *parent;

  public:
      Element() :
        position(vec3(0)), orientation(quat()), scale(vec3(1)), parent(nullptr) { }

      const vec3 &get_position() const {
        return position;
      }

      void set_position(const vec3 &position) {
        this->position = position;
      }

      virtual void render(Glass &glass) override;

      Group *get_parent() const {
        return parent;
      }

      void set_parent(Group *parent) {
        this->parent = parent;
      }

      const quat &get_orientation() const {
        return orientation;
      }

      void set_orientation(const quat &orientation) {
        this->orientation = orientation;
      }

      const vec3 &get_scale() const {
        return scale;
      }

      void set_scale(const vec3 &scale) {
        this->scale = scale;
      }

      mat4 get_transform() const;
  };
}
