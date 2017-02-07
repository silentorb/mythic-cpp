#include "event_utility.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace aura::sequencing;

namespace tuning {

  const string get_event_message(Event &event) {
    const string labels[] = {"NOTE START", "NOTE_END", "CHORD"};
    string label = labels[event.get_type()];
    switch (event.get_type()) {
      case Event_Type::note_start:
      case Event_Type::note_end: {
        auto note_event = static_cast<Note_Event *>(&event);
        auto pitch = note_event->get_note().get_pitch();
        return label + " " + to_string(event.get_absolute_start())
               + " " + to_string(event.get_relative_start())
               + " (" + to_string(event.get_trigger_start())
               + " - " + to_string(event.get_trigger_end()) + ")"
               + " " + get_keyname(pitch->key) + to_string(pitch->index);
//               + " #" + to_string(note_event->get_note().get_id());
      }

      case Event_Type::chord: {
//        auto chord_event = static_cast<Chord_Event *>(&event);
        return "CHORD " + to_string(event.get_absolute_start())
               + " " + to_string(event.get_relative_start())
               + " (" + to_string(event.get_trigger_start())
               + " - " + to_string(event.get_trigger_end()) + ")";
      }
    }

    return "";
  }

  string get_indentation(int steps) {
    string result = "";
    for (int i = 0; i < steps; ++i) {
      result += "    ";
    }
    return result;
  }

  const string get_notation_message(Event &event) {
    switch (event.get_type()) {
      case Event_Type::note_start: {
        auto note_event = static_cast<Note_Event *>(&event);
        auto pitch = note_event->get_note().get_pitch();
        return get_indentation(note_event->get_group_id()) + get_keyname(pitch->key) + to_string(pitch->index) + "\n";
      }

      case Event_Type::chord: {
        auto chord_event = static_cast<Chord_Event *>(&event);
        return string("chord ") + get_keyname(chord_event->get_chord().chord.key) + "\n";
      }
    }

    return "";
  }

  void write_events_to_file(Event_Data &source, const string &filename) {
    ofstream output_file(filename);
    if (output_file.is_open()) {
      for (auto &event : source.get_events()) {
        output_file << get_event_message(*event) + "\n";
      }
    }
  }

  void write_notation_to_file(Event_Data &source, const string &filename) {
    ofstream output_file(filename);
    if (output_file.is_open()) {
      for (auto &event : source.get_events()) {
        output_file << get_notation_message(*event);
      }
    }
  }

}