#pragma once

#include "commoner/dllexport.h"
#include "glm/glm.hpp"
#include "Spatial_Source.h"

using namespace glm;

namespace scenery {

  class Parent;

  class MYTHIC_EXPORT Element : no_copy {

  public:
//      Element() :
//        position(vec3(0)), orientation(quat()), scale(vec3(1)), parent(nullptr) { }

      virtual ~Element();

      virtual void render() = 0;
      virtual void update(float delta) = 0;
      virtual Parent *get_parent() const = 0;;
      virtual void set_parent(Parent *new_parent, bool update_others = true) = 0;
      virtual void remove() = 0;
//      virtual mat4 get_transform() = 0;
//      virtual mat4 get_absolute_orientation() = 0;
//      void get_absolute_position_and_orientation(vec3 &out_position, quat &out_orientation);

//      void move_to_absolute();
  };

  inline Element::~Element() {}
}
