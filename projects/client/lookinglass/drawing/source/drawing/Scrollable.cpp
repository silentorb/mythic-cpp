#include <glm/gtc/matrix_transform.hpp>
#include "Scrollable.h"

namespace drawing {
  Scrollable::Scrollable(Draw &draw) :
    draw(draw), offset(vec2(0, 0)) { }

  void Scrollable::render() {
    auto &image_effect = draw.get_default_image_effect();
    auto transform = glm::translate(mat4(1), vec3(offset.x, offset.y, 0));
    image_effect.modify_projection(transform);
    Group::render();
    image_effect.initialize_projection(draw.get_dimensions());
  }
}