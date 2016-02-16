#include "Image_Effect.h"
#include "lookinglass/glow.h"
#include <glm/gtc/matrix_transform.hpp>
#include "shading/Program.h"
#include <modeling/Simple_Mesh.h>

namespace drawing {
  Image_Effect::Image_Effect(shading::Program &program, const ivec2 &viewport_dimensions) :
    Effect(program) {
    initialize_projection(viewport_dimensions);
  }

  void Image_Effect::initialize_projection(const ivec2 &viewport_dimensions) {
    projection = glm::ortho(0.0f, (float) viewport_dimensions.x, 0.0f, (float) viewport_dimensions.y);
  }

  void Image_Effect::render(const mat4 &transform, modeling::Simple_Mesh &mesh, const mat4 &texture_transform) {
    shading::Effect::activate();
    glEnable(GL_BLEND);

    auto projection_index = glGetUniformLocation(program->get_id(), "projection");
    glUniformMatrix4fv(projection_index, 1, GL_FALSE, (GLfloat *) &projection);

    auto transform_index = glGetUniformLocation(program->get_id(), "transform");
    glUniformMatrix4fv(transform_index, 1, GL_FALSE, (GLfloat *) &transform);

    auto texture_transform_index = glGetUniformLocation(program->get_id(), "texture_transform");
    glUniformMatrix4fv(texture_transform_index, 1, GL_FALSE, (GLfloat *) &texture_transform);

    mesh.render();
  }

  void Image_Effect::modify_projection(mat4 &modifier) {
    projection = projection * modifier;
  }
}