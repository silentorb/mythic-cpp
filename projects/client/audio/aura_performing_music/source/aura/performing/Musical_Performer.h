#pragma once

#include "Musical_Stroke.h"
#include <vector>
#include <memory>
#include <aura/engineering/Buffer.h>
#include <aura/sequencing/Conductor.h>
#include <containment/Mutable_Container.h>
#include "Musical_Performance.h"
#include "Performance_Note.h"
#include "Loop_Manager.h"

using namespace std;

namespace aura {

  namespace sequencing {
    template<typename Event_Type>
    class Sequencer;

    struct Chord_Structure;
  }

  namespace performing {

    template<typename Sound_Type, typename Event_Type>
    class Musical_Performer : no_copy, Stroke_Input<Sound_Type>,
                              public virtual containment::Mutable_Container<Musical_Performance<Sound_Type, Event_Type>> {

        std::vector<Performance_Note<Sound_Type, Event_Type>> events;
        vector<unique_ptr<Sound_Type>> strokes;
        vector<Musical_Performance<Sound_Type, Event_Type>> performances;
//        Loop_Manager loop_manager;
        Tempo_Loop loop;
        double measure_position = 0;
        bool first_update = true;
        sequencing::Conductor &conductor;

    public:
        Musical_Performer(sequencing::Conductor &conductor) :
          loop(conductor.get_sample_rate(), 4), conductor(conductor) {
          loop.set_on_loop([this](Conductor &conductor, double start, double end) {
            measure_position = 0;
            populate_next_measure();
          });
        }

        virtual void add_stroke(unique_ptr<Sound_Type> stroke) override;
        void add_event(Instrument<Sound_Type, Event_Type> &instrument, const Event_Type &note);
//        void perform(Conductor &conductor, Musical_Performance<Sound_Type, Event_Type> &performance, float start,
//                     float end);
        void populate_next_measure();
        float update(float delta);
        void update_notes(float delta);
        float update_strokes(float delta);
        Musical_Performance<Sound_Type, Event_Type> &add_performance(Instrument<Sound_Type, Event_Type> &instrument,
                                                                     const Sequencer_Factory<Event_Type> &sequencer);

        void set_loop_beats(int count) {
          loop.set_beats(count);
        }
        void remove(Musical_Performance<Sound_Type, Event_Type> &performance) override;
        void add(Musical_Performance<Sound_Type, Event_Type> &performance) override;
        void clear() override;
    };

  }
}