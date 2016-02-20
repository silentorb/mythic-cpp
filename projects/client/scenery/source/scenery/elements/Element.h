#pragma once

#include <glm/gtc/quaternion.hpp>
#include "dllexport.h"

#include "lookinglass/Renderable.h"
#include "glm/glm.hpp"
#include "Parent.h"

using namespace lookinglass;
using namespace glm;

namespace scenery {
  class Group;

  class MYTHIC_EXPORT Element : public Renderable, no_copy {
  private:
      vec3 position;
      quat orientation;
      vec3 scale;
      Parent *parent;
      bool visible;

  public:
//      Element() :
//        position(vec3(0)), orientation(quat()), scale(vec3(1)), parent(nullptr) { }

      Element(Parent &parent) :
        position(vec3(0)), orientation(quat()), scale(vec3(1)), parent(&parent), visible(true) {
        parent.add(unique_ptr<Element>(this));
      }

      const vec3 &get_position() const {
        return position;
      }

      void set_position(const vec3 &position) {
        this->position = position;
      }

      virtual void render(Glass &glass) override;

      Parent *get_parent() const {
        return parent;
      }

      void set_parent(Parent *parent) {
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

      virtual mat4 get_transform();

      bool is_visible()const {
        return visible;
      }

      void set_visible(bool value){
        visible = value;
      }
  };
}
