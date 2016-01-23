#include "Sprite.h"
#include "shading/Texture.h"

namespace drawings {
  Sprite::Sprite(shading::Texture *texture, const vec2 &position) : texture(texture), position(position) {

  }

  void Sprite::render(lookinglass::Glass &glass) {
    texture->activate();
  }
}