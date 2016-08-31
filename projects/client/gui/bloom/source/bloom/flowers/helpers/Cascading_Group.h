#pragma once

#include <bloom/flowers/Group.h>

namespace bloom {
  namespace flowers {
    namespace helpers {

      class BLOOM_EXPORT Cascading_Group: public Group {
      public:
          virtual glm::vec2 update_dimensions(const glm::vec2 &parent_dimensions) override;

      };
    }
  }
}