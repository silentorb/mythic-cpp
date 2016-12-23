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

    template<typename Sound_Type, typename Event_Type>
    class Musical_Performer : no_copy {
        vector<unique_ptr<Sound_Type>> strokes;
        vector<Musical_Performance<Sound_Type, Event_Type>> performances;
        vector<unique_ptr<Tempo_Loop>> loops;
        engineering::Engineer &engineer;

    public:
        Musical_Performer(engineering::Engineer &engineer) : engineer(engineer) {}

        void add_stroke(unique_ptr<Sound_Type> stroke);
        void perform(Conductor &conductor, Musical_Performance<Sound_Type, Event_Type> &performance, float start, float end);
        float update(float delta, Conductor &conductor);
        void add_performance(Instrument<Sound_Type, Event_Type> &instrument, Sequencer &sequencer, int group_id);
        Tempo_Loop &get_loop_with_beat_count(float beats);
        void clear_performances();
    };

    void perform_chord_structure(Conductor &conductor, sequencing::Chord_Structure &chord_structure, float start,
                                               float end);
  }
}