#pragma once

#include "dllexport.h"
#include "bloom/flowers/Flower.h"
#include "Modal.h"
#include <stack>

namespace haft {
  class Action;

  class Input_State;
}

namespace lookinglass {
  class House;
}
namespace drawing {
  class Draw;

  class Element;
}

namespace bloom {

  class Text_Flower;

  class BLOOM_EXPORT Garden {
      Flower *root;
      unique_ptr<haft::Action> select_action;
      drawing::Draw &draw;
      Measurement_Converter converter;
      Flower *focused_flower;
      stack <unique_ptr<Modal>> modal_stack;
      static Garden *instance;

  public:
      Garden(drawing::Draw &draw);
      ~Garden();

      void update_input(haft::Input_State &input_state);

      Flower &get_root() const {
        return *root;
      }

      Text_Flower *create_text(const string content, const string font = "default");
      void render();

      drawing::Draw &get_draw() const {
        return draw;
      }

      Flower &create_generic_flower();

      const Measurement_Converter &get_converter() const {
        return converter;
      }

      haft::Action &get_select_action() const {
        return *select_action;
      }

      Flower *get_focused() const {
        return focused_flower;
      }

      void set_focused(Flower *focused_flower) {
        Garden::focused_flower = focused_flower;
      }

      void add_modal(Flower &flower);
      lookinglass::House &get_house() const;

      static Garden &get_instance() {
        return *instance;
      }

      Orientation get_orientation() const;
      Flower *get_modal() const;
      void pop_modal();
  };
}