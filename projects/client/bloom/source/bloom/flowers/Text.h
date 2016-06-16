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
    public:
//        virtual void update_layout(Axis_Measurements & parent_measurements, Axis_Values &parent_bounds) override;
        virtual void render() override;
        Text(const string content, Parent *parent);
        virtual ~Text();

        void set_content(const string &content);
        void set_color(const glm::vec4 value);
        void set_size(float value);
        void set_line_height(float value);
    };
  }
}