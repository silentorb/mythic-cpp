#pragma once

#include <bloom/flowers/Group.h>
#include <bloom/widgetry/Slider.h>
#include <bloom/flowers/Text.h>
#include <nobby/Knob.h>
#include <string>
#include <bloom/flowers/List.h>

namespace {
  using namespace bloom;

  namespace bloom_nobby {

    template<typename T>
    class Knob_Flower : public bloom::flowers::Group {
        flowers::Text *text;
        widgetry::Slider *slider;
        nobby::Knob<T> &knob;

        void initialize() {
          auto list = new flowers::List(flowers::Arrangement::right, 10);
          add_child(list);
          auto text_padding = new flowers::Box();
          list->add_child(text_padding);
          text_padding->set_margins(10);
          text_padding->set_dimensions(100, {Measurements::shrink, 0});
          text = new flowers::Text("");
          text_padding->add_child(text);
          slider = new widgetry::Slider();
          slider->set_width(400);
          slider->set_height(100);
          list->add_child(slider);
        }

        void set_text_value() {
          text->set_content(std::to_string(knob.get_value()));
        }

        void set_slider_value() {
          slider->set_value(knob.get_normalized());
        }

    public:
        Knob_Flower(nobby::Knob<T> &knob) : knob(knob) {
          initialize();
          std::to_string(knob.get_value());
          set_text_value();
          set_slider_value();

          slider->on_changed([&knob, this](float value) {
            knob.set_normalized(value);
            set_text_value();
          });
        }
    };
  }
}