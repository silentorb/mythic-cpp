#pragma once

namespace aura {
  namespace processing {

    class Time_Source {
    public:
        virtual double get_duration() = 0;
        virtual double get_position() = 0;
    };
  }
}