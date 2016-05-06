#pragma once

#include <aura/sequencing/Chord.h>
#include <aura/sequencing/Note.h>
#include "dllexport.h"

namespace aura {

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
      aura::Note note;

  public:
      Note_Event(Event_Type type, const aura::Note &note, double trigger_start, double trigger_end) :
        Event(type, trigger_start, trigger_end), note(note) { }

      const Note &get_note() const {
        return note;
      }

      virtual float get_relative_start() const override {
        return note.get_start();
      }
  };

  class MYTHIC_EXPORT Chord_Event : public Event {
      aura::Chord_Instance chord;
      float relative_start;

  public:
      Chord_Event(const aura::Chord_Instance &chord, float relative_start, double trigger_start, double trigger_end) :
        Event(Event_Type::chord, trigger_start, trigger_end), chord(chord), relative_start(relative_start) { }

      const Chord_Instance &get_chord() const {
        return chord;
      }

      virtual float get_relative_start() const override {
        return relative_start;
      }
  };
}