#pragma once


#include "aura/sequencing/Pitch.h"
#include "Beats.h"

namespace aura {
  namespace sequencing {

    class Note {
        Beats duration;
        const Pitch *pitch;
        float frequency;
        Beats start;
        float velocity = 1;
//        unsigned long id;

    public:
        Note(const Pitch &pitch, Beats start, Beats duration = 1, float velocity = 1);
//      Note(float frequency, float start, float duration = 1);

        const Beats &get_start() const {
          return start;
        }

        const Beats &get_duration() const {
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

        void set_duration(const Beats &value) {
          duration = value;
        }

        void set_start(const Beats &value) {
          start = value;
        }

        Note operator+(const Beats &value) const {
          return Note(*pitch, start + value, duration, velocity);
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