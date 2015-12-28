#pragma once

#include "lookinglass/Renderable.h"
#include "glm/glm.hpp"

using namespace lookinglass;
using namespace glm;

namespace scenery {
  namespace elements {

    class Element : public Renderable {
    private:
        vec3 position;

    public:

        const vec3 &get_position() const {
          return position;
        }

        void set_position(const vec3 &position) {
          this->position = position;
        }
    };
  }
}