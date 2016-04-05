#pragma once

#include <aura/conductor/Buffer.h>
#include "dllexport.h"

namespace aura {
  class Note;

  class MYTHIC_EXPORT Stroke {
      float duration;
      float frequency;
      float progress = 0;

  public:
      Stroke(const Note &note);
      virtual float update( float delta);

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
  };
}