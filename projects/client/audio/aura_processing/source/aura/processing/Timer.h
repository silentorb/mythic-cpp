#pragma once

#include "Time_Source.h"

namespace aura {
  namespace processing {

    class Timer : public Time_Source {
        const double duration;
        double position = -1;

    public:
        Timer(double duration) : duration(duration) {}

        void update(float delta) {
          if (position == -1) {
            position = 0;
          }
          else {
            position += delta;
            if (position > duration)
              position = duration;
          }
        }

        void operator()(float delta) {
          update(delta);
        }

        const double &get_duration() const {
          return duration;
        }

        const double &get_position() const {
          return position;
        }

        virtual double get_duration() override {
          return duration;
        }

        virtual double get_position() override {
          return position;
        }

        const double get_progress() const {
          return position / duration;
        }

        bool is_finished() const {
          return position >= duration;
        }
    };
  }
}