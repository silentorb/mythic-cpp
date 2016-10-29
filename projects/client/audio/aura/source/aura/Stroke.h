#pragma once

#include <aura/engineering/Buffer.h>
#include <functional>

namespace aura {
  namespace sequencing {
    class Conductor;
  }

  class Stroke {
      double duration;

  protected:
      double progress = 0;

  public:
      Stroke(double duration) : duration(duration) {}

      virtual ~Stroke() {}

      virtual float update(float beat_delta) = 0;

      double get_duration() const {
        return duration;
      }

      const double get_position() const {
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