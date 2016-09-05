
#include "Render_Buffer.h"
#include <glow.h>
#include <glow_gl.h>

using namespace glm;

namespace texturing {
  namespace buffering {

    Render_Buffer::Render_Buffer(const glm::ivec2 &dimensions, int format, int multisamples) :
      dimensions(dimensions), format(format), multisamples(multisamples) {
      load();
    }

    Render_Buffer::~Render_Buffer() {

    }

    void Render_Buffer::load() {
      glGenRenderbuffers(1, &id);
      glBindRenderbuffer(GL_RENDERBUFFER, id);
      if (multisamples) {
        glRenderbufferStorageMultisample(GL_RENDERBUFFER, multisamples, format, dimensions.x, dimensions.y);
      }
      else {
        glRenderbufferStorage(GL_RENDERBUFFER, format, dimensions.x, dimensions.y);
      }
      glBindRenderbuffer(GL_RENDERBUFFER, 0);
    }

    void Render_Buffer::release() {
      if (id) {
        glDeleteRenderbuffers(1, &id);
        id = 0;
      }
    }

    void Render_Buffer::activate() {

    }

  }
}