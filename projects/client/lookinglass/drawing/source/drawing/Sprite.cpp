#include "Sprite.h"
#include "texturing/Texture.h"
#include <glm/gtc/matrix_transform.hpp>

namespace drawing {
  Sprite::Sprite(Image_Effect &effect, Texture &texture, const vec2 &position) :
    effect(effect),
    texture(&texture),
    position(position) {

  }

  void Sprite::render(lookinglass::Glass &glass) {
    auto transform = glm::translate(mat4(1), vec3(position.x, glass.get_viewport_dimensions().y - position.y, 0))
                     * glm::scale(mat4(1), vec3(texture->get_width(), texture->get_height(), 1));

    texture->activate();
    effect.render(transform, glass.get_viewport_dimensions());
  }
}