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
    class Performer_Note_Consumer : public Event_Consumer<Event_Type> {
        Musical_Performer<Sound_Type, Event_Type> &performer;
        Instrument<Sound_Type, Event_Type> &instrument;

    public:
        Performer_Note_Consumer(Musical_Performer<Sound_Type, Event_Type> &performer,
                                Instrument<Sound_Type, Event_Type> &instrument) : performer(performer),
                                                                                  instrument(instrument) {}

        void add_event(const Event_Type &note) override {
          performer.add_event(instrument, note);
        }
    };

    template<typename Sound_Type, typename Event_Type>
    void Musical_Performer<Sound_Type, Event_Type>::add_stroke(unique_ptr<Sound_Type> stroke) {
      strokes.push_back(std::move(stroke));
    }

    template<typename Sound_Type, typename Event_Type>
    void Musical_Performer<Sound_Type, Event_Type>::add_event(Instrument<Sound_Type, Event_Type> &instrument,
                                                              const Event_Type &note) {
      for (auto it = events.begin(); it != events.end(); it++) {
        if ((*it).get_note().get_start() > note.get_start()) {
          events.emplace(it, instrument, note);
          return;
        }
      }
      events.emplace_back(instrument, note);
    }

    template<typename Sound_Type, typename Event_Type>
    void Musical_Performer<Sound_Type, Event_Type>::populate_next_measure() {
      std::cout << "next" << std::endl;
      for (auto &performance: performances) {
        Performer_Note_Consumer<Sound_Type, Event_Type> consumer(*this, performance.get_instrument());
        performance.get_sequencer().generate_notes(consumer);
      }
    }

    template<typename Sound_Type, typename Event_Type>
    void Musical_Performer<Sound_Type, Event_Type>::update_notes(float delta) {
      measure_position += delta;
      int played_notes = 0;
      for (auto &event : events) {
        if (event.get_note().get_start() <= measure_position) {
          ++played_notes;
          add_stroke(event.get_instrument().create_sound(event.get_note()));
        }
        else {
          break;
        }
      }

      if (played_notes > 0) {
        events.erase(events.begin(), events.begin() + played_notes);
      }
    }

    template<typename Sound_Type, typename Event_Type>
    float Musical_Performer<Sound_Type, Event_Type>::update_strokes(float delta) {
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
    float Musical_Performer<Sound_Type, Event_Type>::update(float delta) {
      loop.update(conductor);
      if (first_update) {
        populate_next_measure();
        first_update = false;
      }
      update_notes(delta);
      return update_strokes(delta);
    }

//    template<typename Sound_Type, typename Event_Type>
//    Musical_Performance<Sound_Type, Event_Type> &Musical_Performer<Sound_Type, Event_Type>::add_performance(
//      Instrument<Sound_Type, Event_Type> &instrument, const Sequencer_Factory<Event_Type> &sequencer_factory) {
//      auto sequencer = sequencer_factory();
//      performances.push_back(Musical_Performance<Sound_Type, Event_Type>(instrument, sequencer));
//      auto &performance = performances[performances.size() - 1];
//      return performance;
//    }

    template<typename Sound_Type, typename Event_Type>
    void Musical_Performer<Sound_Type, Event_Type>::add(Musical_Performance<Sound_Type, Event_Type> &performance) {
      performances.push_back(std::move(performance));
    }

    template<typename Sound_Type, typename Event_Type>
    void Musical_Performer<Sound_Type, Event_Type>::remove(
      Musical_Performance<Sound_Type, Event_Type> &performance) {
      for (int i = 0; i < performances.size(); ++i) {
        if (&performances[i] == &performance) {
          performances.erase(performances.begin() + i);
          break;
        }
      }
    }

    template<typename Sound_Type, typename Event_Type>
    void Musical_Performer<Sound_Type, Event_Type>::clear() {
      performances.empty();
//      loop_manager.clear();
    }
  }
}
