#pragma once

#include <vector>

namespace aura {
  namespace envelopes {

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

        double get_absolute_position(const double &last_point_position, double duration)const;
    };

    class Custom_Envelope;

    struct Custom_Envelope_Instance {
        double last_point_position = 0;
        double transition_modifier;
        float height_offset = 0;
        int next_point = 0;

        Custom_Envelope_Instance(const Custom_Envelope &envelope, double duration);
    };

    class Custom_Envelope {
        std::vector<Point> points;

        void initialize() {
          for (int i = 0; i < points.size(); ++i) {
            auto &point = points[i];
            if (point.curve == Point::Curve::hold)
              point.level = points[i - 1].level;
          }
        }

    public:
        Custom_Envelope(const std::initializer_list<Point> &points_initializer) : points(points_initializer) {
          initialize();
        }

        Custom_Envelope(const std::vector<Point> &points_initializer) : points(points_initializer) {
          initialize();
        }

        const std::vector<Point> &get_points() const {
          return points;
        }

        float update(Custom_Envelope_Instance &instance, double position, double duration) const;

        void initialize_instance(Custom_Envelope_Instance &instance, double duration) const;
    };
  }
}