#pragma once

namespace aura {
  namespace processing {

    class Timer {
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

        const double get_progress() const {
          return position / duration;
        }

        bool is_finished() const {
          return position >= duration;
        }
    };
  }
}