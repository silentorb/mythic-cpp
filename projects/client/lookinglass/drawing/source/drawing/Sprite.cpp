#include "Sprite.h"
#include "texturing/Image_Info.h"
#include <glm/gtc/matrix_transform.hpp>
#include "Draw.h"

namespace drawing {
  Sprite::Sprite(Draw &draw, Image_Effect &effect, const Image_Info &image, const vec2 &position) :
    draw(draw),
    effect(&effect),
    image(&image),
    position(position) {

  }

  Sprite::Sprite(Draw &draw, const Image_Info &image, const vec2 &position) :
    draw(draw),
    effect(nullptr),
    image(&image),
    position(position) {

  }
  void Sprite::render(lookinglass::Glass &glass) {
    auto transform = glm::translate(mat4(1), vec3(position.x,
                                                  glass.get_viewport_dimensions().y - position.y - image->height, 0))
                     * glm::scale(mat4(1), vec3(image->width, image->height, 1));

    image->sheet->texture->activate();
    effect->render(transform, glass.get_viewport_dimensions());
  }

  const Image_Info& Sprite::get_image() const {
    return *image;
  }
}