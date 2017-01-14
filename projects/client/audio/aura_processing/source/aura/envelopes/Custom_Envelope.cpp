#include <stdexcept>
#include "Custom_Envelope.h"

using namespace std;

namespace aura {
  namespace envelopes {

    double Point::get_absolute_position(const double &last_point_position, double duration) const {
      switch (type) {
        case Point::Position::percentage:
          return position * duration;

        case Point::Position::absolute:
          return position;

        case Point::Position::relative:
          if (position == 5 && level == 1)
            int k = 0;
          return last_point_position + position;

      }

      throw runtime_error("Unsupported envelope point type.");
    }

    inline bool is_past(const Point &point, const double &last_point_position, double position, double duration) {
      auto milestone = point.get_absolute_position(last_point_position, duration);
      return position >= milestone;
    }

    double get_transition_modifier(const vector<Point> &points, Custom_Envelope_Instance &instance,
                                   double duration, double position) {

//      if (instance.next_point == 0) {
//        return get_absolute_position(points[0], instance.last_point_position, stroke);
//      }
//      else
      if (instance.next_point < points.size()) {
        auto previous_position = points[instance.next_point - 1].get_absolute_position(instance.last_point_position,
                                                                                       duration);
        auto next_position = points[instance.next_point].get_absolute_position(previous_position,
                                                                               duration);

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
                     - point.get_absolute_position(position, duration);
        if (range == 0)
          return 0;

        return slope / range;
      }
    }

    float Custom_Envelope::update(Custom_Envelope_Instance &instance, double position, double duration) const {

      while (instance.next_point < points.size()
             && is_past(points[instance.next_point], instance.last_point_position, position, duration)) {
        ++instance.next_point;
        if (instance.next_point < points.size() && points[instance.next_point].curve == Point::Curve::hold) {
        }
        else {
          instance.transition_modifier = get_transition_modifier(points, instance, duration, position);
        }
        instance.last_point_position = position;
      }

      if (instance.next_point < points.size() && points[instance.next_point].curve == Point::Curve::hold) {
        return points[instance.next_point].level;
      }

      if (this->points[0].level > 0.55 && this->points[0].level < 0.56)
        int k = 0;

      auto relative_position = position - instance.last_point_position;
      float result = instance.transition_modifier == 0
                     ? points[instance.next_point].level
                     : (float) (relative_position * instance.transition_modifier) + instance.height_offset;

      if (result < 0 || result > 1) {
        int k = 0;
      }
      if (result < 0)
        result = 0;
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

    void Custom_Envelope::initialize_instance(Custom_Envelope_Instance &instance, double duration) const {
      auto &point = get_points()[0];
      float slope = point.level;
      auto range = point.get_absolute_position(instance.last_point_position, duration);
      instance.transition_modifier = slope / range;
    }

    Custom_Envelope_Instance::Custom_Envelope_Instance(const Custom_Envelope &envelope, double duration) {
      envelope.initialize_instance(*this, duration);
    }
  }
}

