#pragma once

#include <lookinglass/perspective/Camera.h>
#include <lookinglass/House.h>
#include "dllexport.h"
#include "clienting/Client.h"
#include <memory>
#include <lookinglass/perspective/Viewport.h>

using namespace lookinglass::perspective;
using namespace lookinglass;
using namespace clienting;
using namespace std;

namespace laboratory {
  namespace display {
    class MYTHIC_EXPORT Freeform_Camera {
    private:
        unique_ptr<Camera> camera;
    public:
        Freeform_Camera(Viewport &viewport);

        void update(float delta, Client &client);
    };
  }
}