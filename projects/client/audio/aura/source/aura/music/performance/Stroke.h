#pragma once

#include <aura/engineer/Buffer.h>
#include "dllexport.h"
#include <functional>
#include <aura/sequencing/Note.h>

namespace aura {

  class Conductor;

  class MYTHIC_EXPORT Stroke {
      float duration;
      float frequency;
      float progress = 0;
      Note note;

  public:
      Stroke(const Note &note);
      virtual float update(float delta, Conductor &conductor);

      float get_duration() const {
        return duration;
      }

      float get_frequency() const {
        return frequency;
      }

      float get_progress() const {
        return progress;
      }

      bool is_finished() const {
        return progress >= duration;
      }

      const Note &get_note() const {
        return note;
      }
  };

  typedef std::function<Stroke *(const Note &note)> Stroke_Generator;
}