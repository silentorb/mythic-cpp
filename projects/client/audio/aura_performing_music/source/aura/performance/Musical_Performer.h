#pragma once

#include "Musical_Stroke.h"
#include <vector>
#include <memory>
#include <aura/engineering/Buffer.h>
#include <aura/sequencing/Conductor.h>
#include "Instrument_Old.h"
#include "Musical_Performance.h"
#include "Tempo_Loop.h"

using namespace std;

namespace aura {


  namespace sequencing {
    class Sequencer;
    struct Chord_Structure;
  }

  namespace performing {

    class Musical_Performer : no_copy {
        vector<unique_ptr<Musical_Stroke>> strokes;
        vector<Musical_Performance> performances;
        vector<unique_ptr<Tempo_Loop>> loops;
        engineering::Engineer &engineer;

    public:
        Musical_Performer(engineering::Engineer &engineer) : engineer(engineer) {}

        void add_stroke(unique_ptr<Musical_Stroke> stroke);
        void perform(Conductor &conductor, Musical_Performance &performance, float start, float end);
        float update(float delta, Conductor &conductor);
        void add_performance(Instrument_Old &instrument, Sequencer &sequencer, int group_id);
        Tempo_Loop &get_loop_with_beat_count(float beats);
        void clear_performances();
    };

    void perform_chord_structure(Conductor &conductor, sequencing::Chord_Structure &chord_structure, float start,
                                               float end);
  }
}