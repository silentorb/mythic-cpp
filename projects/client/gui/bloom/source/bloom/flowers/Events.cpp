#include <songbird/Song.h>
#include "Events.h"

namespace bloom {

  namespace Events {
    const songbird::Song<Flower_Delegate_Old> activate_old = songbird::Song<Flower_Delegate_Old>();
    const songbird::Song<Flower_Delegate_Old> drag_old = songbird::Song<Flower_Delegate_Old>();
    const songbird::Song<Flower_Delegate_Old> close_old = songbird::Song<Flower_Delegate_Old>();
    const songbird::Song<Flower_Delegate_Old> cancel_old = songbird::Song<Flower_Delegate_Old>();
  };

  namespace Events {
    const songbird::Song<Flower_Delegate> activate = songbird::Song<Flower_Delegate>();
    const songbird::Song<Flower_Delegate> drag = songbird::Song<Flower_Delegate>();
    const songbird::Song<Flower_Delegate> mouse_down = songbird::Song<Flower_Delegate>();
    const songbird::Song<Flower_Delegate> close = songbird::Song<Flower_Delegate>();
    const songbird::Song<Flower_Delegate> cancel = songbird::Song<Flower_Delegate>();
    const songbird::Song<Flower_Delegate> changed = songbird::Song<Flower_Delegate>();
  };
}