#include "Interactive_Singer.h"

namespace bloom {
  namespace flowers {

    void Interactive_Singer::click(Flower_Delegate action) {
      singer->listen((songbird::Song<Flower_Delegate>&)Events::activate_old, action);
    }

    bool Interactive_Singer::check_event(const Event &event) {
      if (singer->has_listeners((songbird::Song<Flower_Delegate>&)event.get_id()) && point_is_inside(get_parent(), event.get_point())) {
        singer->sing((songbird::Song<Flower_Delegate>&)event.get_id(), this);
        return true;
      }

      return false;
    }
  }
}