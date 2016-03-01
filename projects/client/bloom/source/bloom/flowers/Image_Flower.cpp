#include "Image_Flower.h"
#include "drawing/Sprite.h"
#include "drawing/Image.h"

namespace bloom {
  Image_Flower::Image_Flower(Garden &garden, unique_ptr<drawing::Sprite> &sprite) :
    Flower(garden),
    sprite(std::move(sprite)) {

    auto &image = sprite->get_image();
    dimensions.x = image.get_width();
    dimensions.y = image.get_height();
  }

  void Image_Flower::render() {
    sprite->set_position(position);
    sprite->render();
    Flower::render();
  }

}

