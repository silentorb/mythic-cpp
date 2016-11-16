#pragma once

#include "Group.h"
#include <bloom/layout/Axis_Value.h>

namespace bloom {
  namespace flowers {

    class Root : public Group {
        Axis_Values bounds;

    public:
        virtual glm::vec2 update_dimensions(const glm::vec2 &parent_dimensions) override;
        virtual const Axis_Values &get_absolute_bounds() const override;
        
        virtual const string get_class_name() const override {
          return "Root";
        }
    };
  }
}