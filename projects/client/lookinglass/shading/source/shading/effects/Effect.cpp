#include "Effect.h"
#include "shading/Program.h"
#include "lookinglass/glow.h"

namespace shading {

  Effect::Effect(Program &program) :
    program(&program) {

  }

  void Effect::activate() {
    program->activate();
  }

  unsigned int Effect::get_location(const char *name) {
		return glGetUniformLocation(program->get_id(), name);
  }

  void Effect::set_vec4(unsigned int index, const glm::vec4 &value) {
		glUniform4f(index, value.x, value.y, value.z, value.w);
//		glUniform4fv(index, 1, (float*)&value);
	  glow::check_error("Effect::set_vec4");
  }
}
