#pragma once

#include <glm/vec3.hpp>
#include <glm/gtc/quaternion.hpp>

namespace spatial_old {

  using vec3 = glm::vec3;
  using quat = glm::quat;
  using mat4 = glm::mat4;

  class Transform {
      vec3 position;
      quat orientation;
      vec3 scale;
      bool changed;
      Transform *parent = nullptr;
      mat4 matrix;

  public:
      const vec3 &get_position() const {
        return position;
      }

      void set_position(const vec3 &position) {
        Transform::position = position;
        changed = true;
      }

      const quat &get_orientation() const {
        return orientation;
      }

      void set_orientation(const quat &orientation) {
        Transform::orientation = orientation;
        changed = true;
      }

      const vec3 &get_scale() const {
        return scale;
      }

      void set_scale(const vec3 &scale) {
        Transform::scale = scale;
        changed = true;
      }

      bool is_changed() const {
        return changed;
      }

      Transform *get_parent() const {
        return parent;
      }

      void set_parent(Transform *parent) {
        Transform::parent = parent;
        changed = true;
      }

      void modify_position(const vec3 &value) {
        position += value;
        changed = true;
      }

      void modify_orientation(const vec3 value) {
        this->orientation *= quat(value);
        changed = true;
      }

      void modify_orientation(const quat &value) {
        this->orientation *= value;
        changed = true;
      }

      const mat4 &get_matrix();
  };
}