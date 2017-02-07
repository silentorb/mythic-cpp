#pragma once

#include "Musical_Stroke.h"
#include <vector>
#include <memory>
#include <aura/engineering/Buffer.h>
#include <aura/sequencing/Conductor.h>
#include "Musical_Performance.h"
#include "Performance_Note.h"
#include "Loop_Manager.h"

using namespace std;

namespace aura {

  namespace sequencing {
    class Sequencer;

    struct Chord_Structure;
  }

  namespace performing {

    template<typename Sound_Type, typename Event_Type>
    class Musical_Performer : no_copy, Stroke_Input<Sound_Type> {
        std::vector<Performance_Note<Sound_Type, Event_Type>> notes;
        vector<unique_ptr<Sound_Type>> strokes;
        vector<Musical_Performance<Sound_Type, Event_Type>> performances;
        Loop_Manager loop_manager;

    public:
        Musical_Performer(engineering::Engineer &engineer) : loop_manager(engineer) {}

        virtual void add_stroke(unique_ptr<Sound_Type> stroke) override;
        void perform(Conductor &conductor, Musical_Performance<Sound_Type, Event_Type> &performance, float start,
                     float end);
        float update(float delta, Conductor &conductor);
        void add_performance(Instrument<Sound_Type, Event_Type> &instrument, Sequencer &sequencer);
        void clear_performances();
    };

  }
}