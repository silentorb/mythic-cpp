#pragma once

#include "dllexport.h"
#include "Stroke.h"
#include <vector>
#include <memory>
#include <aura/engineer/Buffer.h>
#include <aura/sequencing/Conductor.h>
#include "aura/music/performance/instruments/Instrument.h"
#include "aura/music/performance/instruments/Instrument.h"
#include "Performance.h"
#include "Tempo_Loop.h"

using namespace std;

namespace aura {
  class Instrument;

  class Sequencer;

  class MYTHIC_EXPORT Performer : no_copy {
      vector<unique_ptr<Stroke>> strokes;
      vector<Performance> performances;
      vector<unique_ptr<Tempo_Loop>> loops;
      Engineer &engineer;

  public:
      Performer(Engineer &engineer) : engineer(engineer) { }
      void add_stroke(Stroke *stroke);
      void perform(Conductor &conductor, Instrument &instrument, Sequencer &sequencer, float start, float end);
      float update(float delta, Conductor &conductor);
      void add_performance(Instrument &instrument, Sequencer &sequencer);
      Tempo_Loop &get_loop_with_beat_count(float beats);
      void clear_performances() {
        performances.empty();
      }
  };

  struct Chord_Structure;
  MYTHIC_EXPORT void perform_chord_structure(Conductor &conductor, Chord_Structure &chord_structure, float start,
                                             float end);
}