#include "Knob_Flower.h"

using namespace bloom;

namespace bloom_nobby {

  void Knob_Flower_Internal::initialize(bloom::flowers::Group *flower, const string &label_text) {
    auto list = new flowers::List(flowers::Arrangement::right, 10);
    flower->add_child(list);

    {
      auto text_padding = new flowers::Box();
      list->add_child(text_padding);
      text_padding->set_margins(10);
      text_padding->set_dimensions(150, {Measurements::shrink, 0});
      auto label = new flowers::Text(label_text);
      text_padding->add_child(label);
    }

    {
      auto text_padding = new flowers::Box();
      list->add_child(text_padding);
      text_padding->set_margins(10);
      text_padding->set_dimensions(100, {Measurements::shrink, 0});
      text = new flowers::Text("");
      text_padding->add_child(text);
    }

    slider = new widgetry::Slider();
    slider->set_width(400);
    slider->set_top(0);
    list->add_child(slider);
  }
}
