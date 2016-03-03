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
#include "lookinglass/glow.h"
#include "lookinglass/perspective/Viewport.h"
#include <glm/gtc/matrix_transform.hpp>

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

    float solid_vertices[] = {
//      0, 0,
//      1, 0,
//      1, 1,
//      0, 1

//      1, 0,
//      1, 1,
//      0, 1,
//      0, 0,

      0, 0,
      0, 1,
      1, 1,
      1, 0,
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

    {
      auto program = shader_manager.get_program_or_null("sprite");
      if (!program) {
        program = &shader_manager.create_program_from_files("sprite", "drawing/sprite.vertex",
                                                            "texturing/image.fragment", {});
      }

      default_image_effect = unique_ptr<Image_Effect>(
        new Image_Effect(*program, house.get_base_viewport()));
    }

    flat_program = shader_manager.get_program_or_null("drawing.flat");
    if (!flat_program) {
      flat_program = &shader_manager.create_program_from_files("drawing.flat", "drawing/flat.vertex",
                                                               "drawing/flat.fragment", {});
    }

  }

  Draw::~Draw() { }

  void Draw::add_to_house() {
    auto wrapper = new Renderable_Draw(*this);
    house.add_renderable(*wrapper);
  }

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

  void Draw::draw_square(float left, float top, float width, float height, const vec4 &color, bool solid) {
    flat_program->activate();

    glDisable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    auto &viewport = house.get_base_viewport();
    vec2 scaling = viewport.get_unit_scaling();

    auto transform = glm::translate(mat4(1), vec3(left * scaling.x, top * scaling.y, 0))
                     * glm::scale(mat4(1), vec3(width * scaling.x, height * scaling.y, 1));

//    auto transform = glm::scale(mat4(1), vec3(width, height, 1));

    auto color_index = glGetUniformLocation(flat_program->get_id(), "color");
    glUniform4fv(color_index, 1, (float *) &color);

    //auto scaling_index = glGetUniformLocation(flat_program->get_id(), "scaling");
    //glUniform2fv(scaling_index, 1, (float *) &scaling);

//    auto projection_index = glGetUniformLocation(flat_program->get_id(), "projection");
//    glUniformMatrix4fv(projection_index, 1, GL_FALSE, (GLfloat *) &viewport.get_flat_projection());

    auto transform_index = glGetUniformLocation(flat_program->get_id(), "transform");
    glUniformMatrix4fv(transform_index, 1, GL_FALSE, (GLfloat *) &transform);

    solid_mesh->render(solid);
    glEnable(GL_DEPTH_TEST);
  }

}