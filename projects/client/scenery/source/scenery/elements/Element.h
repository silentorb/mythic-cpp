#pragma once

#include <glm/gtc/quaternion.hpp>
#include "dllexport.h"

#include "glm/glm.hpp"
#include "Parent.h"

using namespace glm;

namespace scenery {

  class MYTHIC_EXPORT Element : no_copy {
  private:
      vec3 position;
      quat orientation;
      vec3 scale;
      Parent *parent = nullptr;
      bool visible;

  public:
//      Element() :
//        position(vec3(0)), orientation(quat()), scale(vec3(1)), parent(nullptr) { }

      Element(Parent *parent) :
        position(vec3(0)), orientation(quat()), scale(vec3(1)), parent(parent), visible(true) {
        if (parent)
          parent->add_child(unique_ptr<Element>(this));
      }

      virtual ~Element() { }

      vec3 &get_position() {
        return position;
      }

      void set_position(const vec3 &position) {
        this->position = position;
      }

      void set_position(float x, float y, float z) {
        this->position = vec3(x, y, z);
      }

      virtual void render();

      Parent *get_parent() const {
        return parent;
      }

      void set_parent(Parent *parent, bool update_other = true) {
        this->parent = parent;
        if (parent && update_other)
          parent->add_child(*this);
      }

      void remove() {
        parent->remove_child(*this);
      }

      const quat &get_orientation() const {
        return orientation;
      }

      void set_orientation(const quat &orientation) {
        this->orientation = orientation;
      }

      vec3 &get_scale() {
        return scale;
      }

      void set_scale(const vec3 &scale) {
        this->scale = scale;
      }

      void set_scale(const float value) {
        this->scale = vec3(value);
      }

      virtual mat4 get_transform();

      bool is_visible() const {
        return visible;
      }

      void set_visible(bool value) {
        visible = value;
      }
  };
}
