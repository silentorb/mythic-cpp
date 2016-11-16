#pragma once

#include <bloom/flowers/Group.h>
#include <bloom/widgetry/Slider.h>
#include <bloom/flowers/Text.h>
#include <nobby/Knob.h>
#include <string>
#include <bloom/flowers/List.h>

namespace bloom_nobby {
}

namespace bloom_nobby {

  struct Knob_Flower_Internal {
      bloom::flowers::Text *text;
      bloom::widgetry::Slider *slider;
      void initialize(bloom::flowers::Group *flower, const std::string &label_text);
  };

  template<typename T>
  class Knob_Flower : public bloom::flowers::Group {
      Knob_Flower_Internal internal;
      nobby::Knob<T> &knob;

      void set_text_value() {
        internal.text->set_content(std::to_string(knob.get_value()));
      }

      void set_slider_value() {
        internal.slider->set_value(knob.get_normalized());
      }

  public:
      Knob_Flower(nobby::Knob<T> &knob, const string &label_text) : knob(knob) {
        internal.initialize(this, label_text);
        std::to_string(knob.get_value());
        set_text_value();
        set_slider_value();

        internal.slider->on_changed([&knob, this](float value) {
          knob.set_normalized(value);
          set_text_value();
        });
      }

      virtual const string get_class_name() const override {
        return "Knob_Flower";
      }

  };
}
