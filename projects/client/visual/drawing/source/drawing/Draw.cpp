#include "lookinglass/Renderable_List.h"
#include "Draw.h"
#include "shading/Shader_Manager.h"
#include "Image_Effect.h"
#include "modeling/Simple_Mesh.h"
#include "lookinglass/House.h"
#include "glow.h"
#include "perspective/Viewport.h"
#include <glm/gtc/matrix_transform.hpp>

using namespace modeling;
using namespace texturing;

namespace drawing {

  Draw::Draw(lookinglass::House &house) :
    house(house),
    solid_vertex_schema(new Vertex_Schema(
      {
        Vertex_Attribute(0, "position", 2),
        Vertex_Attribute(1, "vertex_color", 4)
      }
    )),
    image_vertex_schema(new Vertex_Schema({4})) {

    auto &shader_manager = house.get_shader_manager();

    float solid_vertices[] = {
      0, 0, 1, 1, 1, 1,
      0, 1, 1, 1, 1, 1,
      1, 1, 1, 1, 1, 1,
      1, 0, 1, 1, 1, 1,
    };

    float image_vertices[] = {
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

    square_effect = unique_ptr<Square_Effect>(new Square_Effect(*flat_program));
  }

  Draw::~Draw() {}

  const ivec2 &Draw::get_dimensions() const {
    return house.get_glass().get_viewport_dimensions();
  }

  void Draw::draw_square(float left, float top, float width, float height, Draw_Method draw_method,
                         Square_Effect &effect, Renderable_Mesh &mesh) {

    auto &viewport = house.get_base_viewport();
    vec2 scaling = viewport.get_unit_scaling();

    auto transform = glm::translate(mat4(1), vec3(left * scaling.x, top * scaling.y, 0))
                     * glm::scale(mat4(1), vec3(width * scaling.x, height * scaling.y, 1));

    effect.set_transform(transform);

    mesh.render(draw_method);
    glow::check_error("drew_square");
  }

  void Draw::draw_pixel_square(const glm::vec2 &position, const glm::vec2 &dimensions, bool solid,
                               Square_Effect &effect, Renderable_Mesh &mesh) {

    auto &viewport = house.get_base_viewport();
    vec2 scaling = viewport.get_dimensions();
    auto scaled_position = position / scaling;
    auto scaled_dimensions = dimensions / scaling;
    auto transform = glm::translate(mat4(1), vec3(scaled_position, 0))
                     * glm::scale(mat4(1), vec3(scaled_dimensions.x, -scaled_dimensions.y, 1));

    effect.set_transform(transform);

    mesh.render(solid ? modeling::Draw_Method::triangles : modeling::Draw_Method::line_loop);
    glow::check_error("drew_square");
  }

  void Draw::draw_square(float left, float top, float width, float height, const vec4 &color, bool solid) {
    square_effect->activate();
    square_effect->set_color(color);
    draw_square(left, top, width, height, solid ? modeling::Draw_Method::triangles : modeling::Draw_Method::line_loop,
                *square_effect, *solid_mesh);
  }

  void Draw::set_depth(bool value) {
    glow::set_depth_test(value);
    glow::set_depth_write(value);
  }

  const framing::Frame_Info &Draw::get_frame() const {
    return house.get_frame();
  }

}
