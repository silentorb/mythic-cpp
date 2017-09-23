#pragma once

namespace aura {
  namespace envelopes{

    struct Point {
        enum class Position {
            percentage,
            absolute,
            relative,
        };
        enum class Curve {
            linear,
            hold
        };
        double position;
        float level;
        Position type;
        Curve curve;

    public:
        Point(Position type, double position, float level) :
          type(type), position(position), level(level), curve(Curve::linear) {}

        Point(Position type, double position) :
          type(type), position(position), level(0), curve(Curve::hold) {}

    };

  }
}