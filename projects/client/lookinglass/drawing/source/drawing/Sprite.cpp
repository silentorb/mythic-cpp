#include "Sprite.h"
#include "shading/Texture.h"
#include <glm/gtc/matrix_transform.hpp>

namespace drawing {
  Sprite::Sprite(Image_Effect &effect, shading::Texture *texture, const vec2 &position) :
    effect(effect),
    texture(texture),
    position(position) {

  }

  void Sprite::render() {
    auto transform = glm::translate(mat4(1), vec3(position.x, position.y, 0))
                     * glm::scale(mat4(1), vec3(texture->get_width(), texture->get_height(), 1));

    texture->activate();
    effect.render(transform);
  }
}