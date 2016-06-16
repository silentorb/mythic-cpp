#pragma once

#include "Child.h"
#include <string>
#include <glm/vec4.hpp>

namespace typography {
  class Text;

  class Font;

  class Text_Effect;
}

namespace bloom {
  namespace flowers {

    class BLOOM_EXPORT Text : public Child {
        float size;
        bool dimensions_changed = true;
        unique_ptr<typography::Text> text;

        Axis_Values absolute_bounds = {
          {0, 0},
          {0, 0}
        };

        Axis_Values relative_bounds = {
          {0, 0},
          {0, 0}
        };

    public:
//        virtual void update_layout(Axis_Measurements & parent_measurements, Axis_Values &parent_bounds) override;
        virtual void render() override;
        Text(const string content, Parent *parent);
        virtual ~Text();

        void set_content(const string &content);
        void set_color(const glm::vec4 value);
        void set_size(float value);
        void set_line_height(float value);

        virtual Axis_Values &update_relative(const Parent_Dimensions &parent_dimensions) override {
          return relative_bounds;
        }

        virtual void update_absolute(const glm::vec2 &parent_position) override {

        }

        virtual void update(float delta) override {

        }

        virtual const Axis_Values &get_absolute_bounds() override {
          return absolute_bounds;
        }

    };
  }
}