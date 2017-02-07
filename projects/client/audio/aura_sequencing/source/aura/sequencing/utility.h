#pragma once

namespace aura {
  namespace sequencing {

    inline bool is_inside(float offset, float start, float end) {
      return end > start
      ? offset >= start && offset < end
      : offset >= start || offset < end;
    }
  }
}