#pragma once

#include "dllexport.h"
#include "aura/music/Pitch.h"

namespace aura {

  class MYTHIC_EXPORT Note {
       float duration;
      const Pitch *pitch;
      float frequency;
      float start;

  public:
      Note(const Pitch &pitch, float start, float duration);
      Note(float frequency, float start, float duration);

      const float &get_start() const {
        return start;
      }

      float get_duration() const {
        return duration;
      }

      float get_frequency() const {
        return frequency;
      }

  };
}
