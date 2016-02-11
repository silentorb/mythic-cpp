#include "Sprite_Layer.h"
#include "Image.h"
#include "modeling/Simple_Mesh.h"
#include "texturing/Texture.h"
#include "Draw.h"
#include <glm/gtc/matrix_transform.hpp>

namespace drawing {

  Sprite_Layer::Sprite_Layer(Texture &texture, Image_Effect &effect, Draw &draw) :
    texture(texture), effect(&effect), mesh(new modeling::Simple_Mesh(draw.get_image_vertex_schema())) {
  }

  Sprite_Layer::~Sprite_Layer() { }

  void Sprite_Layer::add_sprite(Sprite &sprite) {
    if (&sprite.get_image().get_texture() != &texture)
      throw runtime_error("Attempted to add sprite to a layer with a different sprite sheet.");

    sprites.push_back(&sprite);
		data.resize(data.size() + 4);
  }

  void Sprite_Layer::render(lookinglass::Glass &glass) {
    if (sprites.size() == 0)
      return;

    auto &dimensions = glass.get_viewport_dimensions();
    for (int i = 0; i < sprites.size(); ++i) {
      Vertex_Data *block = &data[i * 4];
      auto &sprite = *sprites[i];
      int x = sprite.get_position().x;
      int y = sprite.get_position().y;

      auto &image = sprite.get_image();
      block->x = x;
      block->y = y;
      block->u = image.get_left();
      block->v = image.get_top();

      block++;
      block->x = x + image.get_pixel_width();
      block->y = y;
      block->u = image.get_right();
      block->v = image.get_top();

      block++;
      block->x = x + image.get_pixel_width();
      block->y = y + image.get_pixel_height();
      block->u = image.get_right();
      block->v = image.get_bottom();

      block++;
      block->x = x;
      block->y = y + image.get_pixel_height();
      block->u = image.get_left();
      block->v = image.get_bottom();
    }
//      0, 0, 0, 0,
//      1, 0, 1, 0,
//      1, 1, 1, 1,
//      0, 1, 0, 1

//    auto transform = glm::translate(mat4(1), vec3(position.x,
//                                                  glass.get_viewport_dimensions().y - position.y - image->height, 0))
//                     * glm::scale(mat4(1), vec3(image->width, image->height, 1));

    mesh->load((float *) data.data(), sprites.size() * 4);
    texture.activate();
    effect->render(mat4(1)//* glm::scale(mat4(1), vec3(dimensions.x, dimensions.y, 1))
                   * glm::scale(mat4(1), vec3(10, 10, 1))
      , glass.get_viewport_dimensions(), *mesh, mat4(1));
  }
}