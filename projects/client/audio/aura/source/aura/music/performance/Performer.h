#pragma once

#include "dllexport.h"
#include "Stroke.h"
#include <vector>
#include <memory>
#include <aura/engineer/Buffer.h>
#include <aura/sequencing/Conductor.h>
#include "aura/music/performance/instruments/Instrument.h"
#include "aura/music/performance/instruments/Instrument.h"

using namespace std;

namespace aura {
  class Instrument;

  class Sequencer;

  class MYTHIC_EXPORT Performer : no_copy {
      vector<unique_ptr<Stroke>> strokes;

  public:
      void add_stroke(Stroke *stroke);
      void perform(Conductor &conductor, Instrument &instrument, Sequencer &sequencer, float start, float end);
      float update(float delta, Conductor &conductor);
  };

  struct Chord_Structure;
  MYTHIC_EXPORT void perform_chord_structure(Conductor &conductor, Chord_Structure &chord_structure, float start,
                                             float end);
}