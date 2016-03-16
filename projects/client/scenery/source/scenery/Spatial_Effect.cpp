#include "Spatial_Effect.h"
#include "lookinglass/glow.h"
#include "shading/Program.h"

namespace scenery {
  Spatial_Effect::Spatial_Effect(Program &program) :
    Effect(program),
    draw_method(Draw_Method::triangles) {  }

  void Spatial_Effect::activate(mat4 &transform, mat4 &normal_transform) {
    Effect::activate();

    unsigned int model = glGetUniformLocation(program->get_id(), "model");
		if (model != -1) {
			glUniformMatrix4fv(model, 1, GL_FALSE, (float*)&transform);
		}

		unsigned int normal_uniform = glGetUniformLocation(program->get_id(), "normal_transform");
		if (normal_uniform != -1) {
			glUniformMatrix4fv(normal_uniform, 1, GL_FALSE, (float*)&normal_transform);
		}

		unsigned int color_uniform = glGetUniformLocation(program->get_id(), "color");
		if (color_uniform != -1) {
			glUniform4f(color_uniform, 1, 0, 1, 0.3);
		}

		glow::check_error("Spatial Effect::activate()");
	}
}
