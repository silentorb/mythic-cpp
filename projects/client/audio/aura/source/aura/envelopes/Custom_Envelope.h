#pragma once

#include "aura_export.h"
#include <vector>
#include <aura/music/performance/Stroke.h>

namespace aura {
  namespace envelopes {

    struct AURA_EXPORT Point {
        enum class Type {
            percentage,
            absolute,
            relative,
        };
        double position;
        float level;
        Type type;

    public:
        Point(Type type, double position, float level) :
          type(type), position(position), level(level) {}
    };

    struct Custom_Envelope_Instance {
        double last_point_position = 0;
        double current_range;
        int next_point = 0;
    };

    class AURA_EXPORT Custom_Envelope {
        std::vector<Point> points;

    public:
        Custom_Envelope(const std::vector<Point> &points) : points(points) {}

        const std::vector<Point> &get_points() const {
          return points;
        }

        float update(Custom_Envelope_Instance &instance, const Stroke &stroke) const;

        static void initialize_instance(Custom_Envelope_Instance &instance,
                                        const Custom_Envelope &envelope, const Stroke &stroke);
    };
  }
}