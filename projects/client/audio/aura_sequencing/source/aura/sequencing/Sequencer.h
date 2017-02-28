#pragma once

#include "commoner/dllexport.h"
#include "Note.h"
#include "Conductor.h"
#include <functional>
#include <memory>

namespace aura {
  namespace sequencing {

    template<typename Event_Type>
    class Event_Consumer {
    public:
        virtual void add_event(Event_Type &note) = 0;
    };

    template<typename Event_Type = Note>
    class Sequencer {
    public:
        virtual void generate_notes(Event_Consumer<Event_Type> &consumer) = 0;
    };

    template<typename Event_Type = Note>
    using Sequencer_Factory = std::function<std::unique_ptr<Sequencer<Event_Type>>()>;
  }
}