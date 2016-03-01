#pragma once

#include "Box.h"

namespace bloom {

  template<typename T>
  vec2 Box<T>::get_absolute_position() const {
    if (parent)
      return parent->get_absolute_position() + position.get_vec2();

    return converter.convert_position(position);
  }

  template<typename T>
  vec2 Box<T>::get_absolute_dimensions() const {
    return dimensions.get_vec2();
  }

  template<typename T>
  Box<T>::Box(const Measurement_Converter &converter) : converter(converter) { }


}