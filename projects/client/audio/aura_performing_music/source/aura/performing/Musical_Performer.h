#pragma once

#include "Musical_Stroke.h"
#include <vector>
#include <list>
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
    using Event_Buffer = std::list<Performance_Note<Sound_Type, Event_Type>>;

    template<typename Sound_Type, typename Event_Type>
    class Musical_Performer : no_copy, Stroke_Input<Sound_Type>,
                              public virtual containment::Mutable_Container<Musical_Performance<Sound_Type, Event_Type>> {

        Event_Buffer<Sound_Type, Event_Type> event_buffers[2];
        Event_Buffer<Sound_Type, Event_Type> *playing_buffer, *next_buffer;
        vector<unique_ptr<Sound_Type>> strokes;
        vector<Musical_Performance<Sound_Type, Event_Type>> performances;
        Tempo_Loop loop;
        int measure_step = 0;
        int loop_measure_size = 4;
        double measure_position = 0;
        bool first_update = true;
        sequencing::Conductor &conductor;
        void add_event(Instrument<Sound_Type, Event_Type> &instrument, const Event_Type &note,
                       Event_Buffer<Sound_Type, Event_Type> *buffer);

        void swap_buffers();
        void on_measure();

    public:
        Musical_Performer(sequencing::Conductor &conductor);
        virtual void add_stroke(unique_ptr<Sound_Type> stroke) override;
        void add_event(Instrument<Sound_Type, Event_Type> &instrument, Event_Type &note);
        void populate_next_measure();
        float update(float delta);
        void update_notes(float delta);
        float update_strokes(float delta);
        Musical_Performance<Sound_Type, Event_Type> &add_performance(Instrument<Sound_Type, Event_Type> &instrument,
                                                                     const Sequencer_Factory<Event_Type> &sequencer);
        void remove(Musical_Performance<Sound_Type, Event_Type> &performance) override;
        void add(Musical_Performance<Sound_Type, Event_Type> &performance) override;
        void clear() override;
    };

  }
}