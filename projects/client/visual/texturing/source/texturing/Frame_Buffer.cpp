#include "Frame_Buffer.h"
#include <glow_gl.h>
#include <glow.h>
#include <resourceful/Resource_Handler.h>

using namespace resourceful;
using namespace std;
using namespace texturing;
using namespace glm;

namespace texturing {

  Frame_Buffer::Frame_Buffer() {
//    texture = shared_ptr<Texture>(new Texture(dimensions, nullptr, multisamples));
//    resource_handler.add_resource(texture);
    load();
  }

  Frame_Buffer::~Frame_Buffer() {
    release();
  }

  void Frame_Buffer::load() {
    glGenFramebuffers(1, &id);
    glBindFramebuffer(GL_FRAMEBUFFER, id);
  }

  void Frame_Buffer::release() {
    if (id) {
      glDeleteFramebuffers(1, &id);
      id = 0;
    }
  }

  void Frame_Buffer::activate() {
    glBindFramebuffer(GL_FRAMEBUFFER, id);
    glDrawBuffer(GL_FRAMEBUFFER);
  }

  void Frame_Buffer::deactivate() {
    // Probably don't need to unbind this but I'm doing it for now until the code is more battle-tested.
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glDrawBuffer(GL_BACK);
  }

//  void Frame_Buffer::set_dimensions(const glm::ivec2 &value) {
//    if (dimensions == value)
//      return;
//
//    dimensions = value;
////    texture->set_dimensions(value);
//  }

  void Frame_Buffer::attach_texture(texturing::Texture *texture) {
    glFramebufferTexture(GL_DRAW_BUFFER, GL_COLOR_ATTACHMENT0, texture->get_id(), 0);
  }

}