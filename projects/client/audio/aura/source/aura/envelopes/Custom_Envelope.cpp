#include "Custom_Envelope.h"

using namespace std;

namespace aura {
  namespace envelopes {


    inline double get_absolute_position(const Point &point, const double &last_point_position, const Stroke &stroke) {
      switch (point.type) {
        case Point::Position::percentage:
          return point.position * stroke.get_duration();

        case Point::Position::absolute:
          return point.position;

        case Point::Position::relative:
          return last_point_position + point.position;

      }

      throw runtime_error("Unsupported envelope point type.");
    }

    inline bool is_past(const Point &point, const double &last_point_position, const Stroke &stroke) {
      auto milestone = get_absolute_position(point, last_point_position, stroke);
      if (stroke.get_position() >= milestone) {
        int k = 0;
      }
      return stroke.get_position() >= milestone;
    }

    double get_transition_modifier(const vector<Point> &points, Custom_Envelope_Instance &instance,
                                   const Stroke &stroke) {

//      if (instance.next_point == 0) {
//        return get_absolute_position(points[0], instance.last_point_position, stroke);
//      }
//      else
      if (instance.next_point < points.size()) {
        auto next_position = get_absolute_position(points[instance.next_point], instance.last_point_position, stroke);
        auto previous_position = get_absolute_position(points[instance.next_point - 1], instance.last_point_position,
                                                       stroke);

        auto range = next_position - previous_position;
        instance.height_offset = points[instance.next_point - 1].level;
        auto next_level = points[instance.next_point].level;
        float slope = next_level - instance.height_offset;
        return slope / range;
        // The full equation is:
        // relative_position / range * slope + offset.
        // This returned modifier is a distillation of that.
      }
      else {
        auto &point = points[instance.next_point - 1];
        instance.height_offset = point.level;
        auto slope = -point.level;
        auto range = stroke.get_duration()
                     - get_absolute_position(point, instance.last_point_position, stroke);
        return slope / range;
      }
    }

    float Custom_Envelope::update(Custom_Envelope_Instance &instance, const Stroke &stroke) const {

      while (instance.next_point < points.size()
             && is_past(points[instance.next_point], instance.last_point_position, stroke)) {
        ++instance.next_point;
        instance.last_point_position = stroke.get_position();
        if (instance.next_point < points.size() && points[instance.next_point].curve == Point::Curve::hold) {
        }
        else {
          instance.transition_modifier = get_transition_modifier(points, instance, stroke);
        }
      }
      if (instance.next_point < points.size() && points[instance.next_point].curve == Point::Curve::hold) {
        return points[instance.next_point].level;
      }
      auto relative_position = stroke.get_position() - instance.last_point_position;
      float result = (float) (relative_position * instance.transition_modifier)
                     + instance.height_offset;

      if (result < 0 || result > 1) {
        int k = 0;
      }
      return result;
//      if (instance.next_point == 0) {
//        return (float) (points[0].level * stroke.get_position() / instance.current_range);
//      }
//      else if (instance.next_point >= points.size()) {
//        auto next_position = get_absolute_position(points[instance.next_point], instance.last_point_position, stroke);
//        auto previous_position = get_absolute_position(points[instance.next_point - 1], instance.last_point_position,
//                                                       stroke);
//        auto range = next_position - previous_position;
//        auto relative_position =
//      }
//      else {
//
//      }
    }

    void Custom_Envelope::initialize_instance(Custom_Envelope_Instance &instance, const Custom_Envelope &envelope,
                                              const Stroke &stroke) {
      auto &point = envelope.get_points()[0];
      float slope = point.level;
      auto range = get_absolute_position(point, instance.last_point_position, stroke);
      instance.transition_modifier = slope / range;

    }

  }
}
