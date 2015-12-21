#pragma once

#include "glm/glm.hpp"
#include "Viewport_Data.h"
#include "Camera.h"
#include "lookinglass/through/Mist.h"


using namespace glm;
using namespace lookinglass:: through;
namespace lookinglass {
  namespace perspective {

    class Viewport {
    private:
        static Viewport *active_viewport;
        Mist<Viewport_Data> *mist;
        Camera *camera;

    public:
        int width;
        int height;;
        int left;
        int top;
        mat4 view;
        mat4 projection;
        mat4 view_projection;

        float get_aspect_ratio() {
          return (float) width / height;
        }

        static Viewport *get_active_viewport() {
          return active_viewport;
        }

        Viewport(Mist<Viewport_Data> *mist, int width, int height, int left = 0, int top = 0);
    };
  }
}
