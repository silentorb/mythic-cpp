#pragma once

#include <vector>
#include "Point.h"

namespace aura {
  namespace envelopes {

    class Custom_Envelope;

    struct Custom_Envelope_Instance {
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

        void initialize_instance(Custom_Envelope_Instance &instance, double duration) const;
    };
  }
}