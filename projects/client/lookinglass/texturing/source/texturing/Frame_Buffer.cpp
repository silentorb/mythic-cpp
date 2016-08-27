#include "Frame_Buffer.h"
#include <lookinglass/glow_gl.h>
#include <lookinglass/glow.h>

namespace texturing {

  Frame_Buffer::Frame_Buffer(int width, int height) :
    width(width), height(height) {
    load();
  }

  void Frame_Buffer::load() {
    glGenFramebuffers(1, &id);
//    glBindFramebuffer(GL_FRAMEBUFFER, id);
    new texturing::Texture((int) dimensions.x, (int) dimensions.y, nullptr);
  }

  void Frame_Buffer::release() {
    glDeleteFramebuffers(1, &id);
    id = 0;
  }

  void Frame_Buffer::activate() {
    glBindFramebuffer(GL_FRAMEBUFFER, id);
    glDrawBuffer(GL_FRAMEBUFFER);
  }

  void Frame_Buffer::deactivate() {
    // Probably don't need to unbind this but doing it for now until the code is more battle-tested.
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glDrawBuffer(GL_BACK);
  }

  void Frame_Buffer::attach_texture(Texture &texture) {
    glFramebufferTexture(GL_DRAW_BUFFER, GL_COLOR_ATTACHMENT0, texture.get_id(), 0);
  }

}