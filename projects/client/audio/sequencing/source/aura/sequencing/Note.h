#pragma once

#include "dllexport.h"
#include "aura/sequencing/Pitch.h"

namespace aura {

  class MYTHIC_EXPORT Note {
      float duration;
      const Pitch *pitch;
      float frequency;
      float start;
      unsigned long id;

  public:
      Note(const Pitch &pitch, float start, float duration = 1);
//      Note(float frequency, float start, float duration = 1);

      const float &get_start() const {
        return start;
      }

      float get_duration() const {
        return duration;
      }

      float get_frequency() const {
        return frequency;
      }

      const Pitch *get_pitch() const {
        return pitch;
      }

      const unsigned long get_id() const {
        return id;
      }
  };
}
