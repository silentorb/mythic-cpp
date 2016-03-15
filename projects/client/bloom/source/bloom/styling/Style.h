#pragma once

#include "dllexport.h"
#include "Fill.h"
#include "Border.h"
#include <memory>

using namespace std;

namespace bloom {

  class MYTHIC_EXPORT Style {
      unique_ptr<Border> border;
      unique_ptr<Fill> fill;
      shared_ptr<Style> highlighed;
      float padding = 0;// Eventually will be a box but most of the time and for now I just need it even.

  public:
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

      float get_padding() const {
        return padding;
      }

      void set_padding(float padding) {
        Style::padding = padding;
      }
  };
}