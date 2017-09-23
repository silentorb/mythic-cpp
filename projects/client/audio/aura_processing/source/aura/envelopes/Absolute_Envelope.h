#pragma once

#include <vector>
#include "Custom_Envelope.h"

namespace aura {
  namespace envelopes {

    struct Absolute_Point {
        double position;
        float level;

        Absolute_Point(double position, float value) : position(position), level(value) {}
    };

    class Absolute_Envelope {
        std::vector<Absolute_Point> points;

    public:
        Absolute_Envelope(const envelopes::Custom_Envelope &envelope, double duration);

        float update(Custom_Envelope_Instance &instance, double position, double duration) const;

    };
  }
}