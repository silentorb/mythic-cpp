#pragma once

#include <aura/engineer/Buffer.h>
#include "dllexport.h"
#include <functional>
#include <aura/sequencing/Note.h>

using namespace aura::sequencing;

namespace aura {
  namespace sequencing {
    class Conductor;
  }

  class MYTHIC_EXPORT Stroke {
      double duration;
      float frequency;
      Note note;

  protected:
      double progress = 0;

  public:
      Stroke(const Note &note);

      virtual ~Stroke() {}

      virtual float update(float beat_delta) = 0;

      double get_duration() const {
        return duration;
      }

      float get_frequency() const {
        return frequency;
      }

      const double get_progress() const {
        return progress;
      }

      const double get_progress_percentage() const {
        return progress / duration;
      }

      bool is_finished() const {
        return progress >= duration;
      }

      const Note &get_note() const {
        return note;
      }
  };
}