#include <stdexcept>
#include "Absolute_Envelope.h"
#include "Custom_Envelope.h"

using namespace std;

namespace aura {
  namespace envelopes {

    double get_absolute_position(const Point &point, const double &last_point_position, double duration)  {
      switch (point.type) {
        case Point::Position::percentage:
          return point.position * duration;

        case Point::Position::absolute:
          return point.position;

        case Point::Position::relative:
          return last_point_position + point.position;

      }

      throw std::runtime_error("Unsupported envelope point type.");
    }

    Absolute_Envelope::Absolute_Envelope(const envelopes::Custom_Envelope &envelope, double duration) {
      points.reserve(envelope.get_points().size());
      double last_position = 0;

      for (auto &point: envelope.get_points()) {
        points.emplace_back(get_absolute_position(point, last_position, duration), point.level);
      }
    }

    double get_transition_modifier(const vector<Absolute_Point> &points, Custom_Envelope_Instance &instance,
                                   double duration) {

//      if (instance.next_point == 0) {
//        return get_absolute_position(points[0], instance.last_point_position, stroke);
//      }
//      else
      if (instance.next_point < points.size()) {
        auto previous_position = points[instance.next_point - 1].position;
        auto next_position = points[instance.next_point].position;

        auto range = next_position - previous_position;
        instance.height_offset = points[instance.next_point - 1].level;
        auto next_level = points[instance.next_point].level;
        float slope = next_level - instance.height_offset;
        if (slope == 0)
          return 0;

        return slope / range;
        // The full equation is:
        // relative_position / range * slope + offset.
        // This returned modifier is a distillation of that.
      }
      else {
        auto &point = points[instance.next_point - 1];
        instance.height_offset = point.level;
        auto slope = -point.level;
        auto range = duration
                     - point.position;
        if (range == 0)
          return 0;

        return slope / range;
      }
    }

    void Custom_Envelope::initialize_instance(Custom_Envelope_Instance &instance, double duration) const {
      auto &point = get_points()[0];
      float slope = point.level;
      auto range = get_absolute_position(point, 0, duration);
      instance.transition_modifier = slope / range;
    }

    float Absolute_Envelope::update(Custom_Envelope_Instance &instance, double position, double duration) const {

      while (instance.next_point < points.size()
             && position >= points[instance.next_point].position) {
        ++instance.next_point;
        instance.transition_modifier = get_transition_modifier(points, instance, duration);
      }

      auto last_position = instance.next_point > 0
                           ? points[instance.next_point - 1].position
                           : 0;

      auto relative_position = position - last_position;
      float result = instance.transition_modifier == 0
                     ? points[instance.next_point - 1].level
                     : (float) (relative_position * instance.transition_modifier) + instance.height_offset;

      if (result < 0)
        result = 0;

      return result;
    }
  }
}