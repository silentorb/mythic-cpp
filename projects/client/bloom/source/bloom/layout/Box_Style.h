#pragma once

#include "bloom/bloom_export.h"
#include "Measurement.h"

namespace bloom {

  class BLOOM_EXPORT Box_Style {
      unique_ptr<Vector4> padding;
      Box_Style *parent_box = nullptr;

  protected:
      void set_parent_box(Box_Style *value) {
        parent_box = value;
      }

  public:

      virtual ~Box_Style() { }

      const Vector4 *get_padding() const {
        if (!padding.get() && parent_box)
          return parent_box->get_padding();

        return padding.get();
      }

      void set_padding(Measurement &measurement) {
        if (!padding.get())
          padding = unique_ptr<Vector4>(new Vector4());

        padding->set_values(measurement);
      }

      void set_padding(Measurement &horizontal, Measurement &vertical) {
        if (!padding.get())
          padding = unique_ptr<Vector4>(new Vector4());

        padding->set_x_values(horizontal);
        padding->set_y_values(vertical);
      }
  };
}