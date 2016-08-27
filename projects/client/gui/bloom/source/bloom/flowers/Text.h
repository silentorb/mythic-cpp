#pragma once

#include "Common_Flower.h"
#include <string>
#include <glm/vec4.hpp>

namespace typography {
  class Text;

  class Font;

  class Text_Effect;
}

namespace bloom {
  namespace flowers {

    class BLOOM_EXPORT Text : public Common_Flower {
        float size;
        bool dimensions_changed = true;
        unique_ptr<typography::Text> text;
        glm::ivec2 screen_dimensions;

//        Axis_Values absolute_bounds = {
//          {0, 0},
//          {0, 0}
//        };

//        Axis_Values relative_bounds = {
//          {0, 0},
//          {0, 0}
//        };

    public:
//        virtual void update_layout(Axis_Measurements & parent_measurements, Axis_Values &parent_bounds) override;
        virtual void render() override;
        Text(const string &content, Parent *parent);
        virtual ~Text();

        void set_content(const string &content);
        void set_color(const glm::vec4 value);
        void set_size(float value);
        void set_line_height(float value);

        float get_size()const {
          return size;
        }

        virtual bool affects_parent_dimensions() const override {
          return true;
        }

        virtual glm::vec2 update_dimensions(const glm::vec2 &parent_dimensions) override;

        virtual void update_position(const glm::vec2 &parent_position, const glm::vec2 &parent_dimensions) override;

        virtual void update(float delta) override { }

        virtual const Axis_Values &get_absolute_bounds() const override {
          throw runtime_error("Not supported.");
        }

    };
  }
}