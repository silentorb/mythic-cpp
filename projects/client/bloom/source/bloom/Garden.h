#pragma once

#include "dllexport.h"
#include "bloom/flowers/Flower.h"

namespace haft {
  class Action;

  class Input_State;
}

namespace drawing {
  class Draw;

  class Element;
}

namespace bloom {

  class Text_Flower;

  class MYTHIC_EXPORT Garden : drawing::Element {
      Flower *root;
      unique_ptr<haft::Action> select_action;
      drawing::Draw &draw;
      Measurement_Converter converter;

  public:
      Garden(drawing::Draw &draw);
			~Garden();

      void update_input(haft::Input_State &input_state);

      Flower &get_root() const {
        return *root;
      }

      Text_Flower *create_text(const string font, const string content);
      virtual void render() override;

      drawing::Draw &get_draw() const {
        return draw;
      }

      Flower & create_generic_flower();

      const Measurement_Converter &get_converter() const {
        return converter;
      }
  };
}