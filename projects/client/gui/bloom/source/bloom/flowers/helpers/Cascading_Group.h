#pragma once

#include <bloom/flowers/Group.h>

namespace bloom {
  namespace flowers {
    namespace helpers {

      class Cascading_Group: public Group {
      public:
          virtual glm::vec2 update_dimensions(const glm::vec2 &parent_dimensions) override;

          virtual const string get_class_name() const override {
            return "Cascading_Group";
          }
      };
    }
  }
}