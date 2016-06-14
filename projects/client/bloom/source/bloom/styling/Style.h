#pragma once

#include "dllexport.h"
#include "Fill.h"
#include "Border.h"
#include <memory>
#include <bloom/layout/Box_Style.h>
#include "bloom/layout/Measurement.h"

using namespace std;

enum class Overflow : int {
    inherit,
    visible,
    hidden
};

namespace bloom {

  class MYTHIC_EXPORT Style : public Box_Style {
      unique_ptr<Border> border;
      unique_ptr<Fill> fill;
//      shared_ptr<Style> highlighed;
      shared_ptr<Style> parent;
      Overflow overflow;
//      Overflow overflow_y;

  public:

      Style() { }

      Style(const shared_ptr<Style> &parent) : parent(parent) {
        set_parent_box(parent.get());
      }
      Style(Style *parent) : parent(parent) {
        set_parent_box(parent);
      }

      virtual ~Style() override { }

      const Fill *get_fill() const {
        return fill.get();
      }

      void set_fill_color(const vec4 color) {
        if (fill.get() == nullptr)
          fill = unique_ptr<Fill>(new Fill());

        fill->set_color(color);
      }

      const Border *get_border() const {
        return border.get();
      }

      void set_border_color(const vec4 color) {
        if (border.get() == nullptr)
          border = unique_ptr<Border>(new Border());

        border->set_color(color);
      }

//      const Vector4 &get_padding() const {
//        return box_style.get_padding();
//      }
//
//      void set_padding(Measurement &measurement) {
//        box_style.set_padding(measurement);
//      }
      Overflow get_overflow() const {
        if (overflow == Overflow::inherit && parent.get())
          return parent->get_overflow();

        return overflow;
      }

      void set_overflow_x(Overflow overflow) {
        Style::overflow = overflow;
      }

  };
}