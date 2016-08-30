#pragma once

#include "commoner/dllexport.h"

#include "glm/glm.hpp"
#include "Viewport_Data.h"
#include "Camera.h"
#include <vector>
#include <functional>

namespace through {
  template<typename T>
  class Mist;
}

using namespace glm;
using namespace std;

namespace perspective {

  typedef function<void(const ivec2 &)> Vector2_Delegate;

  class MYTHIC_EXPORT Viewport {
  private:
      through::Mist<Viewport_Data> &mist;
      Camera *camera;
      vector<Vector2_Delegate> listeners;

  public:
      ivec2 dimensions;
      ivec2 position;
//        mat4 view;
      mat4 projection;
      mat4 flat_projection;
      float angle = glm::radians(45.0f);
//        mat4 view_projection;

      float get_aspect_ratio() {
        return (float) dimensions.x / dimensions.y;
      }

      static Viewport *get_active_viewport();

      Viewport(through::Mist<Viewport_Data> &mist, int width, int height, int left = 0, int top = 0);
      void set_projection();
      void activate();
      void update_device();

//        Camera &get_camera() const {
//          return *camera;
//        }

      void set_camera(Camera *camera) {
        this->camera = camera;
      }

      bool is_active() const;

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

      const mat4 &get_flat_projection() const {
        return flat_projection;
      }

      void set_dimensions(const ivec2 &value);
      void set_bounds(const ivec2 &position, const ivec2 &dimensions);

      void add_listener(Vector2_Delegate listener) {
        listeners.push_back(listener);
      }

      vec2 get_unit_scaling() const;

      const ivec2 &get_position() const {
        return position;
      }

      void set_position(const glm::ivec2& value);
  };
}
