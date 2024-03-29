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
  }

  namespace performing {

    template<typename Sound_Type, typename Event_Type>
    using Event_Buffer = std::list<Performance_Note<Sound_Type, Event_Type>>;

    template<typename Sound_Type, typename Event_Type= sequencing::Note>
    class Musical_Performer : no_copy, Stroke_Input<Sound_Type>,
                              public virtual containment::Mutable_Container<Musical_Performance<Sound_Type, Event_Type>> {
    public:
        using Update_Delegate = std::function<void(Musical_Performer &)>;

    private:
        Event_Buffer<Sound_Type, Event_Type> event_buffers[2];
        Event_Buffer<Sound_Type, Event_Type> *playing_buffer, *next_buffer;
        vector<unique_ptr<Sound_Type>> strokes;
        vector<Musical_Performance<Sound_Type, Event_Type>> performances;
        Tempo_Loop loop;
        int measure_step = 0;
        int loop_measure_size;
        double measure_position = 0;
        bool first_update = true;
        sequencing::Conductor &conductor;
        Update_Delegate update_delegate;

        void add_event_internal(Instrument<Sound_Type, Event_Type> &instrument, const Event_Type &note,
                                Event_Buffer<Sound_Type, Event_Type> *buffer);

        void swap_buffers();
        void on_measure();

    public:
        Musical_Performer(sequencing::Conductor &conductor, int loop_measure_size);
        virtual void add_stroke(unique_ptr<Sound_Type> stroke) override;
        void add_event(Instrument<Sound_Type, Event_Type> &instrument, const Event_Type &note);
        void populate_next_measure();
        float update(float delta);
        void update_notes(float delta);
        float update_strokes(float delta);

        void set_update_delegate(const Update_Delegate &value) {
          update_delegate = value;
        }

        template<typename Factory>
        Musical_Performance<Sound_Type, Event_Type> &add_performance(Instrument<Sound_Type, Event_Type> &instrument,
                                                                     Factory &sequencer_factory) {
          auto sequencer = sequencer_factory();
          performances.push_back(Musical_Performance<Sound_Type, Event_Type>(instrument, sequencer));
          auto &performance = performances[performances.size() - 1];
          return performance;
        }

        void remove(Musical_Performance<Sound_Type, Event_Type> &performance) override;
        void add(Musical_Performance<Sound_Type, Event_Type> &performance) override;
        void clear() override;
    };

  }
}