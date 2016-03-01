#include "Image_Effect.h"
#include "lookinglass/glow.h"
#include <glm/gtc/matrix_transform.hpp>
#include "shading/Program.h"
#include <modeling/Simple_Mesh.h>
#include "lookinglass/perspective/Viewport.h"

using namespace lookinglass::perspective;

namespace drawing {
  Image_Effect::Image_Effect(shading::Program &program, Viewport &viewport) :
    Effect(program), viewport(viewport) {
  }

  void Image_Effect::render(const mat4 &transform, modeling::Simple_Mesh &mesh, const mat4 &texture_transform) {
    shading::Effect::activate();
    glEnable(GL_BLEND);

    auto projection_index = glGetUniformLocation(program->get_id(), "projection");
    glUniformMatrix4fv(projection_index, 1, GL_FALSE, (GLfloat *) &viewport.get_flat_projection());

    auto transform_index = glGetUniformLocation(program->get_id(), "transform");
    glUniformMatrix4fv(transform_index, 1, GL_FALSE, (GLfloat *) &transform);

    auto texture_transform_index = glGetUniformLocation(program->get_id(), "texture_transform");
    glUniformMatrix4fv(texture_transform_index, 1, GL_FALSE, (GLfloat *) &texture_transform);

    mesh.render();
  }
}