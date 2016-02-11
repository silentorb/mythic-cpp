#include "Sprite.h"
#include "Image.h"
#include <glm/gtc/matrix_transform.hpp>
#include "Draw.h"
#include "texturing/Texture.h"

namespace drawing {
  Sprite::Sprite(Draw &draw, Image_Effect &effect,  Image &image, const vec2 &position) :
    draw(draw),
    effect(&effect),
    image(&image),
    position(position) {

  }

  Sprite::Sprite(Draw &draw,  Image &image, const vec2 &position) :
    draw(draw),
    effect(nullptr),
    image(&image),
    position(position) {

  }

  void Sprite::render(lookinglass::Glass &glass) {
    auto transform = glm::translate(mat4(1), vec3(position.x,
                                                  glass.get_viewport_dimensions().y - position.y - image->get_pixel_height(), 0))
                     * glm::scale(mat4(1), vec3(image->get_pixel_width(), image->get_pixel_height(), 1));

    auto texture_transform = glm::translate(mat4(1), vec3(image->get_left(), image->get_bottom(), 0))
			* glm::scale(mat4(1), vec3(image->get_right() - image->get_left(), image->get_top() - image->get_bottom(), 1));
//    * glm::scale(mat4(1), vec3(image->get_width(), image->get_height(), 1));

    image->get_texture().activate();
    effect->render(transform, glass.get_viewport_dimensions(), draw.get_image_mesh(), texture_transform);
  }

}