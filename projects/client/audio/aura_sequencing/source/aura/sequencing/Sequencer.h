#pragma once

#include "commoner/dllexport.h"
#include "Note.h"
#include "Conductor.h"

namespace aura {
  namespace sequencing {

    class Note_Consumer {
    public:
        virtual void add_note(const Note & note) = 0;
    };

    class Sequencer {
    public:
//        virtual float get_beats() const = 0;
//        virtual int size() const = 0;
//        virtual const Note &get_note(int index, Conductor &conductor) = 0;
        virtual void generate_notes(Note_Consumer& consumer, Conductor &conductor) = 0;
    };
  }
}