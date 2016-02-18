#pragma once

#include "dllexport.h"

#include "glm/glm.hpp"
#include "Viewport_Data.h"
#include "Camera.h"
#include "lookinglass/through/Mist.h"

using namespace glm;
using namespace lookinglass::through;

namespace lookinglass {
  namespace perspective {

    class MYTHIC_EXPORT Viewport {
    private:
        Mist<Viewport_Data> &mist;
        Camera *camera;

    public:
        ivec2 dimensions;
        int left;
        int top;
//        mat4 view;
        mat4 projection;
//        mat4 view_projection;

        float get_aspect_ratio() {
          return (float) dimensions.x / dimensions.y;
        }

        static Viewport *get_active_viewport();

        Viewport(Mist<Viewport_Data> &mist, int width, int height, int left = 0, int top = 0);
        void set_projection();
        void activate();
        void update_device();

//        Camera &get_camera() const {
//          return *camera;
//        }

        void set_camera(Camera &camera) {
          this->camera = &camera;
        }

        int get_width() const {
          return dimensions.x;
        }

        int get_height() const {
          return dimensions.y;
        }

        const ivec2 &get_dimensions() const {
          return dimensions;
        }

        void shoot_ray(const ivec2 &point, vec3 &start, vec3 &end) const;
    };
  }
}
