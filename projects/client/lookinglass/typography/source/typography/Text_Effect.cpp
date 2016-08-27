#include "Text_Effect.h"
#include "lookinglass/glow.h"
#include "shading/Program.h"
#include <glm/gtc/matrix_transform.hpp>
#include "shading/effects/Color_Effect.h"
#include "lookinglass/glow_gl.h"

namespace typography {

  void Text_Effect::activate(const vec4 &color, const mat4 &transform) {
    Color_Effect::activate(color);

    glow::set_blend(true);
    glow::set_blend_function(glow::Blend_Factor::source_alpha, glow::Blend_Factor::one_minus_source_alpha);

    auto transform_index = glGetUniformLocation(program->get_id(), "transform");
    glUniformMatrix4fv(transform_index, 1, GL_FALSE, (GLfloat * ) & transform);

  }
}