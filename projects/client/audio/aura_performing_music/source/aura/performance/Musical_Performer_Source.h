#include <iostream>
#include <aura/sequencing/Note.h>
#include "Musical_Performer.h"
#include "aura/sequencing/Sequencer.h"
#include "aura/sequencing/Chord_Structure.h"
#include <string>
#include <aura/sequencing/Event_Recorder.h>
#include <iostream>

using namespace aura::sequencing;

namespace aura {
  namespace performing {

    template<typename Sound_Type, typename Event_Type>
    class Performer_Note_Consumer : public Note_Consumer {
        Musical_Performer<Sound_Type, Event_Type> &performer;
        Instrument<Sound_Type, Event_Type> &instrument;

    public:
        Performer_Note_Consumer(Musical_Performer<Sound_Type, Event_Type> &performer,
                                Instrument<Sound_Type, Event_Type> &instrument) : performer(performer),
                                                                                  instrument(instrument) {}

        void add_note(const Note &note) override {
          performer.add_note(instrument, note);
        }
    };

    template<typename Sound_Type, typename Event_Type>
    void Musical_Performer<Sound_Type, Event_Type>::add_stroke(unique_ptr<Sound_Type> stroke) {
      strokes.push_back(std::move(stroke));
    }

    template<typename Sound_Type, typename Event_Type>
    void Musical_Performer<Sound_Type, Event_Type>::add_note(Instrument<Sound_Type, Event_Type> &instrument,
                                                             const sequencing::Note &note) {
      notes.emplace_back(instrument, note);
    }

    template<typename Sound_Type, typename Event_Type>
    void Musical_Performer<Sound_Type, Event_Type>::populate_next_measure(Conductor &conductor) {
      std::cout << "next" << std::endl;
      for (auto &performance: performances) {
        Performer_Note_Consumer<Sound_Type, Event_Type> consumer(*this, performance.get_instrument());
        performance.get_sequencer().generate_notes(consumer, conductor);
      }
    }

    template<typename Sound_Type, typename Event_Type>
    void Musical_Performer<Sound_Type, Event_Type>::update_notes(float delta, Conductor &conductor) {
      measure_position += delta;
      int played_notes = 0;
      for (auto &note : notes) {
        if (note.get_note().get_start() <= measure_position) {
          ++played_notes;
          add_stroke(note.get_instrument().create_sound(note.get_note()));
        }
        else {
          break;
        }
      }

      if (played_notes > 0) {
        notes.erase(notes.begin(), notes.begin() + played_notes);
      }
    }

    template<typename Sound_Type, typename Event_Type>
    float Musical_Performer<Sound_Type, Event_Type>::update_strokes(float delta, Conductor &conductor) {
      float result = 0;
      float beat_delta = conductor.get_seconds_tempo() * delta;
      for (int i = strokes.size() - 1; i >= 0; --i) {
        auto &stroke = strokes[i];
        auto value = stroke->update(beat_delta);
        if (stroke->is_finished()) {
          strokes.erase(strokes.begin() + i);
        }
        else {
          result += value;
        }
      }

      return result;
    }

    template<typename Sound_Type, typename Event_Type>
    float Musical_Performer<Sound_Type, Event_Type>::update(float delta, Conductor &conductor) {
      loop.update(conductor);
      update_notes(delta, conductor);
      return update_strokes(delta, conductor);
    }

    template<typename Sound_Type, typename Event_Type>
    void Musical_Performer<Sound_Type, Event_Type>::add_performance(Instrument<Sound_Type, Event_Type> &instrument,
                                                                    Sequencer &sequencer) {
      performances.push_back(Musical_Performance<Sound_Type, Event_Type>(instrument, sequencer));
      auto &performance = performances[performances.size() - 1];
//      auto &loop = loop_manager.get_loop_with_beat_count(sequencer.get_beats());
//      loop.listen([&, performance](Conductor &conductor, float start, float end) mutable {
//        perform(conductor, performance, start, end);
//      });
    }

    template<typename Sound_Type, typename Event_Type>
    void Musical_Performer<Sound_Type, Event_Type>::clear_performances() {
      performances.empty();
//      loop_manager.clear();
    }
  }
}
