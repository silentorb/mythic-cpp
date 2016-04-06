#pragma once

#include "dllexport.h"
#include "Stroke.h"
#include <vector>
#include <memory>
#include <aura/engineer/Buffer.h>
#include <aura/music/sequencing/Conductor.h>
#include "Instrument.h"

using namespace std;

namespace aura {
  class Instrument;

  class Sequencer;

  class MYTHIC_EXPORT Performer : no_copy {
      vector<unique_ptr<Stroke>> strokes;

  public:
      void add_stroke(Stroke *stroke);
      void perform(Conductor &conductor, Stroke_Generator &generate, Sequencer &sequencer, float start, float end);
      float update(float delta);
  };

  struct Chord_Structure;
  MYTHIC_EXPORT void perform_chord_structure(Conductor &conductor, Chord_Structure &chord_structure, float start,
                                             float end);
}