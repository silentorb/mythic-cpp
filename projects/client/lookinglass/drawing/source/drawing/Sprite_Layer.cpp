#include "Sprite_Layer.h"
#include "texturing/Image_Info.h"
#include "modeling/Simple_Mesh.h"

namespace drawing {

  Sprite_Layer::Sprite_Layer(Sprite_Sheet &sheet, Image_Effect &effect) :
    sheet(sheet), effect(&effect) {
  }

  Sprite_Layer::~Sprite_Layer() { }

  void Sprite_Layer::add_sprite(Sprite &sprite) {
    if (sprite.get_image().sheet != &sheet)
      throw runtime_error("Attempted to add sprite to a layer with a different sprite sheet.");

    sprites.push_back(&sprite);
    data.resize(sprites.size() + 4);
  }

  void Sprite_Layer::render(lookinglass::Glass &glass) {
    if (sprites.size() == 0)
      return;

    for (int i = 0; i < sprites.size(); ++i) {
      Vertex_Data *block = &data[i * 4];
      auto &sprite = *sprites[i];
      Image_Info &image = sprite.get_image();
      block->x = sprite.get_position().x;
      block->y = sprite.get_position().y;
      block->u = image.x / image.sheet->width;
      block->v = image.y / image.sheet->height;

      block++;
      block->x = block->x + ;
      block->y = sprite.get_position().y;
      block->u = image.x / image.sheet->width;
      block->v = image.y / image.sheet->height;

//      block->v = sprite.get_position().y;
    }

//    auto transform = glm::translate(mat4(1), vec3(position.x,
//                                                  glass.get_viewport_dimensions().y - position.y - image->height, 0))
//                     * glm::scale(mat4(1), vec3(image->width, image->height, 1));

    sheet.texture->activate();
    effect->render(mat4(1), glass.get_viewport_dimensions());
  }
}