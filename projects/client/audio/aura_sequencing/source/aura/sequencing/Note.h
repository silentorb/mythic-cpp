#pragma once

#include "commoner/dllexport.h"
#include "aura/sequencing/Pitch.h"

namespace aura {
  namespace sequencing {

    class Note {
        float duration;
        const Pitch *pitch;
        float frequency;
        float start;
        float velocity = 1;
//        unsigned long id;

    public:
        Note(const Pitch &pitch, float start, float duration = 1);
//      Note(float frequency, float start, float duration = 1);

        const float &get_start() const {
          return start;
        }

        const float &get_duration() const {
          return duration;
        }

        const float &get_frequency() const {
          return frequency;
        }

        const Pitch *get_pitch() const {
          return pitch;
        }

        float get_velocity() const {
          return velocity;
        }

        void set_velocity(float value) {
          velocity = value;
        }
//        const unsigned long get_id() const {
//          return id;
//        }

//        inline bool is_inside(float start, float end) const {
//          return end > start
//                 ? this->start >= start && this->start < end
//                 : this->start >= start || this->start < end;
//        }
    };
  }
}