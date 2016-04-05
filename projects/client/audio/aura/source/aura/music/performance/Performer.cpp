#include <iostream>
#include "Performer.h"
#include "aura/music/sequencing/Sequence.h"

namespace aura {


  void Performer::add_stroke(Stroke *stroke) {
    std::cout << "Added note" << std::endl;
    strokes.push_back(unique_ptr<Stroke>(stroke));
  }

  void Performer::perform(Stroke_Generator & generate, Sequence &sequence, float start, float end) {
    if (end == start)
      return;

    start *= sequence.get_seconds();
    end *= sequence.get_seconds();

    if (end > start) {
      for (auto &note:sequence.get_notes()) {
        if (note.get_start() >= start && note.get_start() < end) {
         /* if (strokes.size() == 1)
            throw runtime_error("error");*/
          add_stroke(generate(note));
        }
      }
    }
    else {
      for (auto &note:sequence.get_notes()) {
        if (note.get_start() >= start || note.get_start() < end) {
					//if (strokes.size() == 1)
					//	throw runtime_error("error");
          add_stroke(generate(note));
        }
      }
    }
  }

  float Performer::update(float delta) {
    for (int i = strokes.size() - 1; i >= 0; --i) {
      auto &stroke = strokes[i];
      auto result = stroke->update(delta);
      if (stroke->is_finished()) {
        strokes.erase(strokes.begin() + i);
        std::cout << "Removed note" << std::endl;
      }
      return result;
    }
  }


}
