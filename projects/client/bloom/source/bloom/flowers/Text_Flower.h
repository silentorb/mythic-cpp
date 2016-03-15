#pragma once

#include "dllexport.h"
#include <string>
#include "Flower.h"

namespace typography {
  class Text;

  class Font;

  class Text_Effect;
}

namespace drawing {
  class Draw;
}

namespace bloom {

  class MYTHIC_EXPORT Text_Flower : public Flower {
      unique_ptr<typography::Text> text;
//      unique_ptr<Measurement> estimated_width;
      bool dimensions_changed = true;

  public:
      Text_Flower(Garden &garden, typography::Font &font, typography::Text_Effect &effect,
                  const string content = "");
      Text_Flower(const string content, Flower *parent);
      ~Text_Flower();

      void set_content(const string &content);
      void set_color(const vec4 value);
      void set_size(float value);

      virtual void render() override;
      virtual void update_absolute_dimensions(Axis_Values parent_values, vec2 margin) override;


  };
}