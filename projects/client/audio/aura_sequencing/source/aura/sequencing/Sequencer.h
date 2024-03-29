#pragma once


#include "Note.h"
#include "Conductor.h"
#include <functional>
#include <memory>

namespace aura {
  namespace sequencing {

    template<typename Event_Type>
    class Event_Consumer {
    public:
        virtual void add_event(const Event_Type &note) = 0;
    };

    template<typename Event_Type = Note>
    class Sequencer {
    public:
        virtual void generate_notes(Event_Consumer<Event_Type> &consumer, const Beats range) = 0;
    };

    template<typename Event = Note>
    using Sequencer_Pointer = std::unique_ptr<Sequencer<Event>>;

    template<typename Event_Type = Note>
    using Sequencer_Factory_Function = std::function<std::unique_ptr<Sequencer<Event_Type>>()>;

    template<typename Event_Type = Note>
    class Sequencer_Factory {
    public:
        virtual std::unique_ptr<Sequencer<Event_Type>> operator()() = 0;
    };

  }
}