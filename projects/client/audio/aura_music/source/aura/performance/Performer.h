#pragma once

#include "commoner/dllexport.h"
#include "Musical_Stroke.h"
#include <vector>
#include <memory>
#include <aura/engineering/Buffer.h>
#include <aura/sequencing/Conductor.h>
#include "Instrument.h"
#include "Performance.h"
#include "Tempo_Loop.h"

using namespace std;

namespace aura {
  namespace performance {
    class Instrument;
  }

  namespace sequencing {
    class Sequencer;
  }

  class MYTHIC_EXPORT Performer : no_copy {
      vector<unique_ptr<Musical_Stroke>> strokes;
      vector<Performance> performances;
      vector<unique_ptr<Tempo_Loop>> loops;
      Engineer &engineer;

  public:
      Performer(Engineer &engineer) : engineer(engineer) {}

      void add_stroke(Musical_Stroke *stroke);
      void perform(Conductor &conductor, Performance &performance, float start, float end);
      float update(float delta, Conductor &conductor);
      void add_performance(Instrument &instrument, Sequencer &sequencer, int group_id);
      Tempo_Loop &get_loop_with_beat_count(float beats);
      void clear_performances();
  };

  namespace sequencing {
    struct Chord_Structure;
  }

  MYTHIC_EXPORT void perform_chord_structure(Conductor &conductor, Chord_Structure &chord_structure, float start,
                                             float end);
}