#include "Viewport.h"
#include <glm/gtc/matrix_transform.hpp>
#include "lookinglass/glow.h"
#include "lookinglass/through/Mist.h"

namespace perspective {
  Viewport *active_viewport = NULL;

  Viewport::Viewport(lookinglass::through::Mist <Viewport_Data> &mist, int width, int height, int left, int top) :
    mist(mist),
    dimensions(ivec2(width, height)),
    position(left, top),
    camera(nullptr) {
    set_projection();
  }

  void Viewport::set_projection() {
		if (dimensions.x == 0 || dimensions.y == 0)
			return;

    projection = glm::perspective(angle, get_aspect_ratio(), 0.1f, 600.0f);
    flat_projection = glm::ortho(0.0f, (float) dimensions.x, 0.0f, (float) dimensions.y);
  }

  Viewport *Viewport::get_active_viewport() {
    return active_viewport;
  }

  void Viewport::activate() {
    if (active_viewport == this)
      return;

    active_viewport = this;

    glViewport(position.x, position.y, dimensions.x, dimensions.y);
    update_device();
  }

  void Viewport::update_device() {
    if (camera == nullptr)
      return;

    if (angle != camera->get_angle()) {
      angle = camera->get_angle();
      set_projection();
    }

    auto data = Viewport_Data();
    data.view = camera->get_view_matrix();
    data.projection = projection;
    data.camera_direction = camera->get_orientation() * vec3(0, 1, 0);
    mist.update(&data);
  }

  void Viewport::shoot_ray(const ivec2 &point, vec3 &start, vec3 &end) const {
//      float x = (2.0f * point.x) / dimensions.x - 1.0f;
//      float y = 1.0f - (2.0f * point.y) / dimensions.y;
//      vec4 ray_clip = vec4(x, 1, y, 1.0);
//      vec4 ray_eye = inverse(projection) * ray_clip;
//      ray_eye = vec4(ray_eye.x, ray_eye.y, -1.0, 0.0);
//      vec3 ray_wor = vec3(inverse(camera->get_view_matrix()) * ray_eye);
//      ray_wor = glm::normalize(ray_wor);

    int y = dimensions.y - point.y;
    auto bounds = vec4(position.x, position.y, dimensions.x, dimensions.y);

    start = glm::unProject(vec3(float(point.x), float(y), 0), camera->get_view_matrix(), projection, bounds);
    end = glm::unProject(vec3(float(point.x), float(y), 1), camera->get_view_matrix(), projection, bounds);

  }

  void Viewport::set_bounds(const ivec2 &new_position, const ivec2 &new_dimensions) {
    dimensions = new_dimensions;
    position = new_position;

    set_projection();
    glViewport(position.x, position.y, dimensions.x, dimensions.y);
		glow::check_error("changing viewport bounds");

    for (auto &listener: listeners) {
      listener(dimensions);
    }
  }

  void Viewport::set_dimensions(const ivec2 &value) {
    if (dimensions == value)
      return;

    set_bounds(position, value);
  }

  vec2 Viewport::get_unit_scaling() const {
//    return dimensions.x > dimensions.y
//           ? vec2(1, (float) ((dimensions.x - dimensions.y) / 2) / dimensions.y)
//           : vec2((float) ((dimensions.y - dimensions.x) / 2) / dimensions.x, 1);
    return dimensions.x < dimensions.y
           ? vec2(1, (float) dimensions.x / dimensions.y)
           : vec2((float) dimensions.y / dimensions.x, 1);
  }
}