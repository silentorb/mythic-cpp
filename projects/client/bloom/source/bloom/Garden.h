#pragma once

#include "dllexport.h"
#include "flowers/Flower.h"

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

  public:
      Garden(drawing::Draw &draw);

      void update_input(haft::Input_State &input_state);

      Flower &get_root() const {
        return *root;
      }

      Text_Flower *create_text(const string font, const string content);
      virtual void render() override;
  };
}