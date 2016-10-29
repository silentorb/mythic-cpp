#pragma once

#include <aura/sequencing/Chord.h>
#include <aura/sequencing/Note.h>
#include "commoner/dllexport.h"

namespace aura {
  namespace sequencing {

    enum Event_Type {
        note_start,
        note_end,
        chord
    };

    class MYTHIC_EXPORT Event : no_copy {
        Event_Type type;
        double absolute_start = -1;
        double trigger_start;
        double trigger_end;

    public:

        Event(Event_Type type, double trigger_start, double trigger_end) :
          type(type), trigger_start(trigger_start), trigger_end(trigger_end) { }

        Event_Type get_type() const {
          return type;
        }

        double get_absolute_start() const {
          return absolute_start;
        }

        void set_absolute_start(double absolute_start) {
          Event::absolute_start = absolute_start;
        }

        double get_trigger_start() const {
          return trigger_start;
        }

        double get_trigger_end() const {
          return trigger_end;
        }

        virtual float get_relative_start() const = 0;
    };

    class MYTHIC_EXPORT Note_Event : public Event {
        Note note;
        int group_id;

    public:
        Note_Event(Event_Type type, const Note &note, double trigger_start, double trigger_end, int group_id) :
          Event(type, trigger_start, trigger_end), note(note), group_id(group_id) { }

        const Note &get_note() const {
          return note;
        }

        virtual float get_relative_start() const override {
          return note.get_start();
        }

        int get_group_id() const {
          return group_id;
        }
    };

    class MYTHIC_EXPORT Chord_Event : public Event {
        Chord_Instance chord;
        float relative_start;

    public:
        Chord_Event(const Chord_Instance &chord, float relative_start, double trigger_start, double trigger_end) :
          Event(Event_Type::chord, trigger_start, trigger_end), chord(chord), relative_start(relative_start) { }

        const Chord_Instance &get_chord() const {
          return chord;
        }

        virtual float get_relative_start() const override {
          return relative_start;
        }
    };
  }
}