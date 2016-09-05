#include "lookinglass/Renderable_List.h"
#include "Draw.h"
#include <texturing/Texture.h>
#include "shading/Vertex_Schema.h"
#include "shading/Shader_Manager.h"
#include "Image_Effect.h"
#include "modeling/Simple_Mesh.h"
#include "lookinglass/House.h"
#include "glow.h"
#include "perspective/Viewport.h"
#include <glm/gtc/matrix_transform.hpp>
#include "glow_gl.h"

using namespace modeling;
using namespace texturing;

namespace drawing {

  Draw::Draw(lookinglass::House &house) :
    house(house),
    solid_vertex_schema(new Vertex_Schema(
      {
        Vertex_Attribute(0, "position", 2),
        Vertex_Attribute(1, "color", 4)
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

  }

  Draw::~Draw() {}

  const ivec2 &Draw::get_dimensions() const {
    return house.get_glass().get_viewport_dimensions();
  }

  void Draw::draw_square(float left, float top, float width, float height, bool solid,
                         shading::Program &program, Renderable_Mesh &mesh) {
    glow::set_depth_test(false);
    glow::set_depth_write(false);
    glow::set_blend(true);
    glow::set_blend_function(glow::Blend_Factor::source_alpha, glow::Blend_Factor::one_minus_source_alpha);

    auto &viewport = house.get_base_viewport();
    vec2 scaling = viewport.get_unit_scaling();

    auto transform = glm::translate(mat4(1), vec3(left * scaling.x, top * scaling.y, 0))
                     * glm::scale(mat4(1), vec3(width * scaling.x, height * scaling.y, 1));

    auto transform_index = glGetUniformLocation(program.get_id(), "transform");
    glUniformMatrix4fv(transform_index, 1, GL_FALSE, (GLfloat *) &transform);

    mesh.render(solid ? modeling::Draw_Method::triangles : modeling::Draw_Method::lines);
    glow::check_error("drew_square");
  }

  void Draw::draw_square(float left, float top, float width, float height, const vec4 &color, bool solid) {
    flat_program->activate();
    auto color_index = glGetUniformLocation(flat_program->get_id(), "color");
    glUniform4fv(color_index, 1, (float *) &color);
    draw_square(left, top, width, height, solid, *flat_program, *solid_mesh);
  }

  void Draw::set_depth(bool value) {
    glow::set_depth_test(value);
    glow::set_depth_write(value);
  }

  const framing::Frame_Info &Draw::get_frame() const {
    return house.get_frame();
  }

}
