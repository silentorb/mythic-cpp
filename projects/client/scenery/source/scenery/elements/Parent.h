#pragma once

#include "dllexport.h"
#include <memory>
#include "glm/glm.hpp"

using namespace std;
using namespace glm;

namespace scenery {

  class Element;

  class MYTHIC_EXPORT Parent {
  public:
      virtual void add(unique_ptr<Element> element) = 0;
      virtual bool has_transform() = 0;
      virtual mat4 get_transform() = 0;
      virtual void move_element(unique_ptr<Element> &element, Parent &destination) = 0;
      virtual void move_element(Element &element, Parent &destination) = 0;
  };
}