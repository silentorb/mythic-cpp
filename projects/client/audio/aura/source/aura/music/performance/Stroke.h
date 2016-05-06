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
      Note note;

  protected:
      double progress = 0;

  public:
      Stroke(const Note &note);
      virtual float update(float beat_delta) = 0;

      float get_duration() const {
        return duration;
      }

      float get_frequency() const {
        return frequency;
      }

      const double get_progress() const {
        return progress;
      }

      bool is_finished() const {
        return progress >= duration;
      }

      const Note &get_note() const {
        return note;
      }
  };

//  typedef std::function<Stroke *(const Note &note)> Instrument;
}