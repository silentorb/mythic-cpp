#pragma once

#include <glm/gtc/quaternion.hpp>
#include "commoner/dllexport.h"
#include "Simple_Element.h"

namespace scenery {

  class MYTHIC_EXPORT Spatial : public Simple_Element, virtual public Spatial_Source {
      vec3 position;
      quat orientation;
      vec3 scale;
      mat4 transform;
      mat4 orientation_transform;

  public:
      Spatial();
      ~Spatial() {}

      vec3 &get_position() {
        return position;
      }

      void set_position(const vec3 &position) {
        this->position = position;
      }

      void set_position(float x, float y, float z) {
        this->position = vec3(x, y, z);
      }

      void modify_position(const vec3 &value) {
        position += value;
      }

      quat &get_orientation() {
        return orientation;
      }

      void set_orientation(const quat &orientation) {
        this->orientation = orientation;
      }

      void set_orientation(const vec3 value) {
        this->orientation = quat(value);
      }

      void modify_orientation(const vec3 value) {
        this->orientation *= quat(value);
      }

      void modify_orientation(const quat &value) {
        this->orientation *= value;
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

      vec3 get_absolute_position() {
        return vec3(get_transform()[3]);
      }

      virtual mat4 &get_absolute_orientation();
      virtual mat4 &get_transform();


  };
}