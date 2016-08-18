#include "Custom_Envelope.h"

using namespace std;

namespace aura {
  namespace envelopes {


    inline double get_absolute_position(const Point &point, const double &last_point_position, const Stroke &stroke) {
      switch (point.type) {
        case Point::Type::percentage:
          return point.position / stroke.get_percentage();

        case Point::Type::absolute:
          return point.position;

        case Point::Type::relative:
          return last_point_position + point.position;

      }

      throw runtime_error("Unsupported envelope point type.");
    }

    inline bool is_past(const Point &point, const double &last_point_position, const Stroke &stroke) {
      return get_absolute_position(point, last_point_position, stroke) >= stroke.get_position();
    }

    double get_current_range(const vector<Point> &points, Custom_Envelope_Instance &instance, const Stroke &stroke) {
      if (instance.next_point == 0) {
        return get_absolute_position(points[0], instance.last_point_position, stroke);
      }
      else if (instance.next_point >= points.size()) {
        auto next_position = get_absolute_position(points[instance.next_point], instance.last_point_position, stroke);
        auto previous_position = get_absolute_position(points[instance.next_point - 1], instance.last_point_position,
                                                       stroke);
        return next_position - previous_position;
      }
      else {
        return stroke.get_duration()
               - get_absolute_position(points[instance.next_point - 1], instance.last_point_position, stroke);
      }
    }

    float Custom_Envelope::update(Custom_Envelope_Instance &instance, const Stroke &stroke) const {

      while (instance.next_point < points.size()
             && is_past(points[instance.next_point], instance.last_point_position, stroke)) {
        ++instance.next_point;
        instance.last_point_position = stroke.get_position();
        instance.current_range = get_current_range(points, instance, stroke);
      }

      auto relative_position = stroke.get_position() - instance.last_point_position;

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
      instance.current_range = get_absolute_position(envelope.get_points()[0], instance.last_point_position, stroke);

    }

  }
}

