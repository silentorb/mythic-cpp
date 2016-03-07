#pragma once

#include <perspective/Camera.h>
#include <lookinglass/House.h>
#include "dllexport.h"
#include "clienting/Client.h"
#include <memory>
#include <perspective/Viewport.h>

namespace haft {
  class Event;
}

using namespace perspective;
using namespace lookinglass;
using namespace clienting;
using namespace std;

namespace laboratory {
  namespace display {
    class MYTHIC_EXPORT Freeform_Camera {
    private:
        unique_ptr<Camera> camera;
        void process_event(haft::Event &event,float delta);
        void move_entity(Positioned_Oriented& player, vec3 direction, float amount);
    public:
        Freeform_Camera(Viewport &viewport);

        void update(float delta, Client &client);
    };
  }
}