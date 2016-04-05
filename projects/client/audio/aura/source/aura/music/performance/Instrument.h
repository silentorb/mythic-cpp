#pragma once

#include "dllexport.h"
#include "Stroke.h"
#include <functional>

namespace aura {

//  class MYTHIC_EXPORT Instrument {
//  public:
//      virtual Stroke *create_stroke(const Note &note) = 0;
//  };

  typedef std::function<Stroke *(const Note &note)> Stroke_Generator;
}
