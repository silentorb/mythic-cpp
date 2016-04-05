#pragma once

#include "dllexport.h"
#include "Stroke.h"
#include <vector>
#include <memory>
#include <aura/conductor/Buffer.h>
#include "Instrument.h"

using namespace std;

namespace aura {
  class Instrument;
  class Sequence;

  class MYTHIC_EXPORT Performer : no_copy {
      vector<unique_ptr<Stroke>> strokes;

  public:
      void add_stroke(Stroke *stroke);
      void perform(Stroke_Generator & generate, Sequence &sequence, float start, float end);
      float update(float delta);
  };
}