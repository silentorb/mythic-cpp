#include "Doorway.h"
#include "glm/glm.hpp"
#include "lookinglass/glow.h"
#include <stdexcept>
#include "lookinglass/glow_gl.h"

using namespace glm;

namespace lookinglass {
  namespace through {

    Doorway::Doorway(int id, const Field_Type &type, int offset)
      : id(id), offset(offset), type(type) {
      updater = determine_updater(type);
    }

    void update_matrix(int index, void *matrix) {
      glUniformMatrix4fv(index, 1, GL_FALSE, (GLfloat *) matrix);
    }

    void update_vector3(int index, void *pointer) {
      auto vector = (vec3 *) pointer;
      glUniform3f(index, vector->x, vector->y, vector->z);
    }

    void update_int(int index, void *pointer) {
      glUniform1i(index, *(int *) pointer);
    }

    void update_float(int index, void *pointer) {
      glUniform1f(index, *(int *) pointer);
    }

    Doorway_Delegate Doorway::determine_updater(const Field_Type &type) {
      switch (type) {
        case Field_Type::matrix:
          return update_matrix;

        case Field_Type::vector3:
          return update_vector3;

        case Field_Type::integer:
          return update_int;

        case Field_Type::floating_point:
          return update_float;
      }

			throw std::runtime_error("Invalid field type.");
    }

    void Doorway::update(void *data) {
      updater(id, ((char *) data) + offset);
    }

  }
}