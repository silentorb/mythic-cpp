#pragma once

#include "bloom/old/Flower_Old.h"
#include "bloom/garden/Modal.h"
#include <stack>
#include <string>
#include <bloom/garden/Garden_Input.h>
#include <bloom/flowers/Parent.h>
#include <bloom/flowers/Group.h>
#include "Draw_Interface.h"

namespace haft {
  class Action;

  class Input_State;
}

namespace drawing {
  class Element;
}

namespace framing {
  class Mutable_Frame;
}

namespace bloom {

  class Text_Flower;

  class BLOOM_EXPORT Garden {
      shared_ptr<Style> default_style;
      unique_ptr<flowers::Group> root;
      unique_ptr<haft::Action> select_action;
      Draw_Interface &draw;
      Measurement_Converter converter;
      flowers::Flower *focused_flower;
      stack<unique_ptr<Modal>> modal_stack;
      static Garden *instance;
      float text_scale = 1;
      Garden_Input garden_input;
      flowers::Flower &get_event_root() const;

  public:
      Garden(Draw_Interface &draw);
      ~Garden();

      void update_input(haft::Input_State &input_state);
      void update(float delta);

      flowers::Group &get_root() const {
        return *root;
      }

      Text_Flower *create_text(const string content, const string font = "default");
      void render();

      Draw_Interface &get_draw() const {
        return draw;
      }

      const Measurement_Converter &get_converter() const {
        return converter;
      }

      haft::Action &get_select_action() const {
        return *select_action;
      }

      flowers::Flower *get_focused() const {
        return focused_flower;
      }

      void set_focused(flowers::Flower *focused_flower) {
        Garden::focused_flower = focused_flower;
      }

      void add_modal(Flower_Old &flower);
      void add_modal(flowers::Flower &flower);

      static Garden &get_instance() {
        return *instance;
      }

      Orientation get_orientation() const;
      flowers::Flower *get_modal() const;
      void pop_modal();

      shared_ptr<Style> &get_default_style() {
        return default_style;
      }

      void update_layout();
      const framing::Frame_Info &get_frame() const;

      const float &get_text_scale() const {
        return text_scale;
      }

      void set_text_scale(float text_scale) {
        Garden::text_scale = text_scale;
      }

      const Garden_Input &get_input() const {
        return garden_input;
      }
  };
}