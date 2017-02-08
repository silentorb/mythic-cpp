#pragma once

#include "commoner/dllexport.h"
#include "Note.h"
#include "Conductor.h"

namespace aura {
  namespace sequencing {

    template<typename Event_Type>
    class Event_Consumer {
    public:
        virtual void add_event(const Event_Type &note) = 0;
    };

    template<typename Event_Type>
    class Sequencer {
    public:
//        virtual float get_beats() const = 0;
//        virtual int size() const = 0;
//        virtual const Note &get_note(int index, Conductor &conductor) = 0;
        virtual void generate_notes(Event_Consumer<Event_Type> &consumer, Conductor &conductor) = 0;
    };
  }
}