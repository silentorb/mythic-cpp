#include <iostream>
#include <aura/sequencing/Note.h>
#include "Musical_Performer.h"
#include "aura/sequencing/Sequencer.h"
#include "aura/sequencing/Chord_Structure.h"
#include <string>
#include <aura/sequencing/Event_Recorder.h>

using namespace aura::sequencing;

namespace aura {
  namespace performing {

    template<typename Sound_Type, typename Event_Type>
    void Musical_Performer<Sound_Type, Event_Type>::add_stroke(unique_ptr<Sound_Type> stroke) {
      strokes.push_back(std::move(stroke));
    }

    template<typename Sound_Type, typename Event_Type>
    void Musical_Performer<Sound_Type, Event_Type>::perform(Conductor &conductor,
                                                            Musical_Performance<Sound_Type, Event_Type> &performance,
                                                            float start, float end) {
      if (end == start)
        return;

      performance.update(*this, conductor, start, end);
    }

    template<typename Sound_Type, typename Event_Type>
    float Musical_Performer<Sound_Type, Event_Type>::update(float delta, Conductor &conductor) {
      loop_manager.update(conductor);

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
    void Musical_Performer<Sound_Type, Event_Type>::add_performance(Instrument<Sound_Type, Event_Type> &instrument,
                                                                    Sequencer &sequencer) {
      performances.push_back(Musical_Performance<Sound_Type, Event_Type>(instrument, sequencer));
      auto &performance = performances[performances.size() - 1];
      auto &loop = loop_manager.get_loop_with_beat_count(sequencer.get_beats());
      loop.listen([&, performance](Conductor &conductor, float start, float end) mutable {
        perform(conductor, performance, start, end);
      });
    }

    template<typename Sound_Type, typename Event_Type>
    void Musical_Performer<Sound_Type, Event_Type>::clear_performances() {
      performances.empty();
      loop_manager.clear();
    }
  }
}
