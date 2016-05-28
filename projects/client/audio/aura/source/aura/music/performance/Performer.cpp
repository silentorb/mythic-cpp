#include <iostream>
#include <aura/sequencing/Note.h>
#include "Performer.h"
#include "aura/sequencing/Sequencer.h"
#include "aura/sequencing/Chord_Structure.h"
#include <string>
#include <aura/sequencing/Event_Recorder.h>

namespace aura {

  void Performer::add_stroke(Stroke *stroke) {
    strokes.push_back(unique_ptr<Stroke>(stroke));
  }

  void Performer::perform(Conductor &conductor, Instrument &instrument, Sequencer &sequencer,
                          float start, float end) {
    if (end == start)
      return;

    start *= sequencer.get_beats();
    end *= sequencer.get_beats();

    for (int i = 0; i < sequencer.size(); ++i) {
      auto &note = sequencer.get_note(i, conductor);
      auto offset = note.get_start();
      auto is_inside = end > start
                       ? note.get_start() >= start && offset < end
                       : note.get_start() >= start || offset < end;

      if (is_inside) {
//        std::cout << "Added note " << note.get_start() << " " << note.get_pitch()->name << std::endl;
        add_stroke(instrument.generate_stroke(note));
        auto recorder = conductor.get_recorder();
        if (recorder)
          recorder->add_event(new Note_Event(Event_Type::note_start, note, start, end));
      }
    }
  }

  float Performer::update(float delta, Conductor &conductor) {
    for (auto &loop: loops) {
      loop->update(conductor);
    }

    float result = 0;
    float beat_delta = conductor.get_seconds_tempo() * delta;
    for (int i = strokes.size() - 1; i >= 0; --i) {
      auto &stroke = strokes[i];
      auto value = stroke->update(beat_delta);
      if (stroke->is_finished()) {
//        std::cout << "Removed note" << std::endl;
        auto recorder = conductor.get_recorder();
        if (recorder)
          recorder->add_event(
            new Note_Event(Event_Type::note_end, stroke->get_note(), stroke->get_duration(), stroke->get_progress()));

        strokes.erase(strokes.begin() + i);
      }
      else {
        result += value;
      }
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

        conductor.set_chord(chord, offset, start, end);
      }
    }
  }

  Tempo_Loop &Performer::get_loop_with_beat_count(float beats) {
    for (auto &loop:loops) {
      if (loop->get_beats() == beats)
        return *loop;
    }

    auto loop = new Tempo_Loop(engineer, beats);
    loops.push_back(unique_ptr<Tempo_Loop>(loop));
    return *loop;
  }

  void Performer::add_performance(Instrument &instrument, Sequencer &sequencer) {
    performances.push_back(Performance(instrument, sequencer));
    auto &loop = get_loop_with_beat_count(sequencer.get_beats());
    loop.listen([&](Conductor &conductor, float start, float end) {
      perform(conductor, instrument, sequencer, start, end);
    });
  }
}
