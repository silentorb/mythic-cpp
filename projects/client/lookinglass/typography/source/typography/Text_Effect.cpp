#include "Text_Effect.h"
#include "lookinglass/glow.h"
#include "shading/Program.h"
#include <glm/gtc/matrix_transform.hpp>
#include "shading/effects/Color_Effect.h"

namespace typography {

  void Text_Effect::activate(const vec4 &color, const mat4 &transform) {
    Color_Effect::activate(color);

    glow::set_blend(true);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

//    glm::mat4 projection = glm::ortho(0.0f, (float) viewport_dimensions.x, 0.0f, (float) viewport_dimensions.y);
//
//    auto projection_index = glGetUniformLocation(program->get_id(), "projection");
//    glUniformMatrix4fv(projection_index, 1, GL_FALSE, (GLfloat *) &projection);

    auto transform_index = glGetUniformLocation(program->get_id(), "transform");
    glUniformMatrix4fv(transform_index, 1, GL_FALSE, (GLfloat *) &transform);

  }
}