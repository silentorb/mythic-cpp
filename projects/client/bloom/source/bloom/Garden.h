#pragma once

#include "bloom/flowers/Flower.h"
#include "Modal.h"
#include <stack>
#include <string>
#include "Draw_Interface.h"

namespace haft {
  class Action;

  class Input_State;
}

namespace drawing {
  class Element;
}

namespace bloom {

  class Text_Flower;

  class BLOOM_EXPORT Garden {
      shared_ptr<Style> default_style;
      Flower *root;
      unique_ptr<haft::Action> select_action;
      Draw_Interface &draw;
      Measurement_Converter converter;
      Flower *focused_flower;
      stack <unique_ptr<Modal>> modal_stack;
      static Garden *instance;

  public:
      Garden(Draw_Interface &draw);
      ~Garden();

      void update_input(haft::Input_State &input_state);

      Flower &get_root() const {
        return *root;
      }

      Text_Flower *create_text(const string content, const string font = "default");
      void render();

      Draw_Interface &get_draw() const {
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

      static Garden &get_instance() {
        return *instance;
      }

      Orientation get_orientation() const;
      Flower *get_modal() const;
      void pop_modal();

      shared_ptr<Style> &get_default_style() {
        return default_style;
      }

      void update_layout();
  };
}