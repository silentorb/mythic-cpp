#pragma once

#include <string>
#include "Flower_Old.h"

namespace typography {
  class Text;

  class Font;

  class Text_Effect;
}

namespace drawing {
  class Draw;
}

namespace bloom {

  class BLOOM_EXPORT Text_Flower : public Flower_Old {
      unique_ptr<typography::Text> text;
//      unique_ptr<Measurement> estimated_width;
      bool dimensions_changed = true;
      float size;

  public:
      Text_Flower(Garden &garden, typography::Font &font, typography::Text_Effect &effect,
                  const string content = "");
      Text_Flower(const string content, Flower_Old *parent);
      ~Text_Flower();

      void set_content(const string &content);
      void set_color(const vec4 value);
      void set_size(float value);
      void set_line_height(float value);

      virtual void render() override;
      virtual void update_absolute_dimensions(const Axis_Values &parent_values, const vec2 margin) override;


  };
}