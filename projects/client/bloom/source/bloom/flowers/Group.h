#pragma once

#include "Parent_Implementation.h"

namespace bloom {
  namespace flowers {

    class BLOOM_EXPORT Group : public Parent_Implementation {
    public:
        virtual glm::vec2 update_dimensions(const glm::vec2 &parent_dimensions) override;
        virtual void update_position(const glm::vec2 &parent_position, const glm::vec2 &parent_dimensions) override;

        virtual bool affects_parent_dimensions() const override {
          return true;
        }
    };
  }
}