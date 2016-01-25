#include "Image_Effect.h"
#include "lookinglass/glow.h"
#include <glm/gtc/matrix_transform.hpp>
#include "shading/Program.h"

namespace drawing {
  Image_Effect::Image_Effect(shading::Program &program, modeling::Simple_Mesh &mesh) :
    Effect(program),
    mesh(mesh) {

  }

  void Image_Effect::render(const mat4 &transform, const ivec2 &viewport_dimensions) {
    shading::Effect::activate();
    glDisable(GL_BLEND);
    glm::mat4 projection = glm::ortho(0.0f, (float) viewport_dimensions.x, 0.0f, (float) viewport_dimensions.y);

    auto projection_index = glGetUniformLocation(program->get_id(), "projection");
    glUniformMatrix4fv(projection_index, 1, GL_FALSE, (GLfloat *) &projection);

    auto transform_index = glGetUniformLocation(program->get_id(), "transform");
    glUniformMatrix4fv(transform_index, 1, GL_FALSE, (GLfloat *) &transform);

    mesh.render();
  }
}