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
//        Loop_Manager loop_manager;
        Tempo_Loop loop;
        double measure_position = 0;
        bool first_update = true;

    public:
        Musical_Performer(engineering::Engineer &engineer) : loop(engineer, 4) {
          loop.set_on_loop([this](Conductor &conductor, double start, double end) {
            measure_position = 0;
            populate_next_measure(conductor);
          });
        }

        virtual void add_stroke(unique_ptr<Sound_Type> stroke) override;
        void add_note(Instrument<Sound_Type, Event_Type> &instrument, const sequencing::Note &note);
//        void perform(Conductor &conductor, Musical_Performance<Sound_Type, Event_Type> &performance, float start,
//                     float end);
        void populate_next_measure(Conductor &conductor);
        float update(float delta, Conductor &conductor);
        void update_notes(float delta, Conductor &conductor);
        float update_strokes(float delta, Conductor &conductor);
        void add_performance(Instrument<Sound_Type, Event_Type> &instrument, Sequencer &sequencer);
        void clear_performances();
    };

  }
}