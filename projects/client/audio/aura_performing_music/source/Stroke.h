#pragma once

#include <aura/engineering/Buffer.h>
#include <functional>
#include <aura/performing/Sound.h>

namespace aura {

  class Stroke : public performing::Sound<float> {
      double duration;

  protected:
      double progress = -1;

  public:
      Stroke(double duration) : duration(duration) {}

      virtual ~Stroke() {}

//      virtual float update(float beat_delta) = 0;

      const double &get_duration() const {
        return duration;
      }

      const double &get_position() const {
        return progress;
      }

      const double get_percentage() const {
        return progress / duration;
      }

      bool is_finished() const {
        return progress >= duration;
      }
  };
}