#include "lookinglass/Renderable_List.h"
#include "Draw.h"
#include <texturing/Texture.h>
#include "modeling/Vertex_Schema.h"
#include "shading/Shader_Manager.h"
#include "Image_Effect.h"
#include "Sprite.h"
#include "modeling/Simple_Mesh.h"
#include "Sprite_Layer.h"
#include "lookinglass/House.h"

using namespace modeling;
using namespace texturing;

namespace drawing {

  class Renderable_Draw : public lookinglass::Renderable {
      Draw &draw;
  public:
      Renderable_Draw(Draw &draw) : draw(draw) { }

      virtual void render(lookinglass::Glass &glass) override {
        draw.render();
      }
  };

  Draw::Draw(lookinglass::House &house) :
    house(house),
    solid_vertex_schema(new Vertex_Schema({2})),
    image_vertex_schema(new Vertex_Schema({4})) {

    auto &shader_manager = house.get_shader_manager();
    auto wrapper = new Renderable_Draw(*this);
    house.add_renderable(*wrapper);

    float solid_vertices[] = {
      -1, -1,
      -1, 1,
      1, 1,
      1, -1,
    };

    float image_vertices[] = {
//      -1, -1, 0, 1,
//      -1, 1, 1, 1,
//      1, 1, 1, 0,
//      1, -1, 0, 0

      0, 0, 0, 0,
      1, 0, 1, 0,
      1, 1, 1, 1,
      0, 1, 0, 1
    };

    solid_mesh = unique_ptr<Simple_Mesh>(new Simple_Mesh(solid_vertices, 4, *solid_vertex_schema.get()));
    image_mesh = unique_ptr<Simple_Mesh>(new Simple_Mesh(image_vertices, 4, *image_vertex_schema.get()));

    auto program = shader_manager.get_program_or_null("sprite");
    if (!program) {
      program = &shader_manager.create_program_from_files("sprite", "drawing/sprite.vertex",
                                                          "texturing/image.fragment", {});
    }
    default_image_effect = unique_ptr<Image_Effect>(
      new Image_Effect(*program, house.get_glass().get_viewport_dimensions()));
  }

  Draw::~Draw() { }

  Sprite *Draw::create_sprite(Image &image, const glm::vec2 &position) {
    auto sprite = new Sprite(*this, *default_image_effect, image, position);
//    add(*sprite);
    return sprite;
  }

  Sprite_Layer &Draw::create_sprite_layer(Texture &texture) {
    auto layer = new Sprite_Layer(texture, *default_image_effect, *this);
    return *layer;
  }

  const ivec2 &Draw::get_dimensions() const {
    return house.get_glass().get_viewport_dimensions();
  }

}