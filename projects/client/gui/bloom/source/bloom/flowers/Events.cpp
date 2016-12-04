#include <songbird/Song.h>
#include "Events.h"

namespace bloom {

  namespace Events {
//    const songbird::Song<Flower_Delegate_Old> activate_old = songbird::Song<Flower_Delegate_Old>();
//    const songbird::Song<Flower_Delegate_Old> drag_old = songbird::Song<Flower_Delegate_Old>();
//    const songbird::Song<Flower_Delegate_Old> close_old = songbird::Song<Flower_Delegate_Old>();
//    const songbird::Song<Flower_Delegate_Old> cancel_old = songbird::Song<Flower_Delegate_Old>();
  };

  namespace Events {
    const Event_Id activate = Event_Id();
    const Event_Id drag = Event_Id();
    const Event_Id mouse_down = Event_Id();
    const Event_Id changed = Event_Id();
    const Event_Id activate_old = Event_Id();
    const Event_Id close = Event_Id();
    const Event_Id changed_old = Event_Id();
  };
}