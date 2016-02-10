#include "Draw.h"
#include <texturing/Texture.h>
#include <texturing/Texture_From_File.h>
#include "modeling/Vertex_Schema.h"
#include "shading/Shader_Manager.h"
#include "Image_Effect.h"
#include "Sprite.h"
#include "texturing/Image_Info.h"
#include "modeling/Simple_Mesh.h"
#include "Sprite_Layer.h"

using namespace modeling;
using namespace texturing;

namespace drawing {

  Draw::Draw(shading::Shader_Manager &shader_manager) :
    solid_vertex_schema(new Vertex_Schema({2})),
    image_vertex_schema(new Vertex_Schema({4})) {
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

    default_image_effect = unique_ptr<Image_Effect>(
      new Image_Effect(shader_manager.get_program("image"), *image_mesh));
  }

  Draw::~Draw() { }

  Sprite &Draw::create_sprite(const texturing::Image_Info &image, const glm::vec2 &position) {
    auto sprite = new Sprite(*this, *default_image_effect, image, position);
    sprites.push_back(unique_ptr<Sprite>(sprite));
    return *sprite;
  }

  void Draw::add_sprite_sheet(texturing::Sprite_Sheet &sheet, const string &filename) {
    auto texture = new Texture(new Texture_From_File(filename));
    sheet.texture = texture;
  }

  Sprite_Layer &Draw::create_sprite_layer(Sprite_Sheet &sheet) {
    auto layer = new Sprite_Layer(sheet, *default_image_effect);
    return *layer;
  }
}