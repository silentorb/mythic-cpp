
#include "Render_Buffer.h"
#include <glow.h>
#include <glow_gl.h>

using namespace glm;

namespace texturing {
  namespace buffering {

    Render_Buffer::Render_Buffer(const glm::ivec2 &dimensions, int multisamples) :
      dimensions(dimensions), multisamples(multisamples) {
      load();
    }

    Render_Buffer::~Render_Buffer() {

    }

    void Render_Buffer::load() {
      glGenRenderbuffers(1, &id);
      glBindRenderbuffer(GL_RENDERBUFFER, id);
      if (multisamples) {
        glRenderbufferStorageMultisample(GL_RENDERBUFFER, multisamples, GL_RGBA, dimensions.x, dimensions.y);
      }
      else {
        glRenderbufferStorage(GL_RENDERBUFFER, GL_RGBA, dimensions.x, dimensions.y);
      }
    }

    void Render_Buffer::release() {

    }

    void Render_Buffer::activate() {

    }

  }
}