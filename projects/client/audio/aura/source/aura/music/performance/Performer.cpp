#include <iostream>
#include <aura/music/sequencing/Note.h>
#include "Performer.h"
#include "aura/music/sequencing/Sequencer.h"
#include "aura/music/sequencing/Chord_Structure.h"
#include <string>

namespace aura {

  void Performer::add_stroke(Stroke *stroke) {
    strokes.push_back(unique_ptr<Stroke>(stroke));
  }

  void Performer::perform(Conductor &conductor, Stroke_Generator &generate, Sequencer &sequencer,
                          float start, float end) {
    if (end == start)
      return;

    start *= sequencer.get_beats();
    end *= sequencer.get_beats();

    for (int i = 0; i < sequencer.size(); ++i) {
      auto &note = sequencer.get_note(i, conductor);
      auto is_inside = end > start
                       ? note.get_start() >= start && note.get_start() < end
                       : note.get_start() >= start || note.get_start() < end;

      if (is_inside) {
        std::cout << "Added note " << note.get_start()<< " "  << note.get_pitch()->name << std::endl;
        /* if (strokes.size() == 1)
                throw runtime_error("error");*/
        add_stroke(generate(note));
      }
    }
//    }
//    else {
//      for (auto &note:sequence.get_notes()) {
//        if (note.get_start() >= start || note.get_start() < end) {
//					//if (strokes.size() == 1)
//					//	throw runtime_error("error");
//          add_stroke(generate(note));
//        }
//      }
  }

  float Performer::update(float delta) {
    float result = 0;
    for (int i = strokes.size() - 1; i >= 0; --i) {
      auto &stroke = strokes[i];
      auto value = stroke->update(delta);
      if (stroke->is_finished()) {
        strokes.erase(strokes.begin() + i);
//        std::cout << "Removed note" << std::endl;
      }
      result = value;
    }

    return result;
  }

  void perform_chord_structure(Conductor &conductor, Chord_Structure &chord_structure, float start, float end) {
    if (end == start)
      return;

    start *= chord_structure.get_measures();
    end *= chord_structure.get_measures();

    auto chords = chord_structure.get_chords();
    float offset = 0;
    for (auto &chord: chords) {
      auto is_inside = end > start
                       ? offset >= start && offset < end
                       : offset >= start || offset < end;

      offset += chord.duration;
      if (is_inside) {
        std::cout << "Chord changed " << get_keyname(chord.chord.key) << std::endl;
        /* if (strokes.size() == 1)
           throw runtime_error("error");*/
        conductor.set_chord(chord.chord);
      }
    }
  }


}
