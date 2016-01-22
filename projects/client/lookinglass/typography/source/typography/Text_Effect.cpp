#include "Text_Effect.h"
#include "lookinglass/glow.h"
#include "shading/Program.h"
#include <glm/gtc/matrix_transform.hpp>
#include "shading/effects/Color_Effect.h"

namespace typography {

  void Text_Effect::activate(const vec4 &color, const ivec2 &viewport_dimensions, const ivec2 &position, float scale) {

    Color_Effect::activate(color);
    glm::mat4 projection = glm::ortho(0.0f, (float)viewport_dimensions.x, 0.0f, (float)viewport_dimensions.y);

    auto projection_index = glGetUniformLocation(program->get_id(), "projection");
    glUniformMatrix4fv(projection_index, 1, GL_FALSE, (GLfloat *)&projection);
    auto position_index = glGetUniformLocation(program->get_id(), "position");
    glUniform2f(position_index,
                position.x,
                viewport_dimensions.y - position.y);

    glUniform2f(glGetUniformLocation(program->get_id(), "scale"), scale, scale);
  }
}