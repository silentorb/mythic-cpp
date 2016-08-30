#include "Frame_Buffer.h"
#include <glow_gl.h>
#include <glow.h>
#include <resourceful/Resource_Handler.h>
#include <glm/vec4.hpp>

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
  void Frame_Buffer::check_complete() {
    auto complete = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    if (complete != GL_FRAMEBUFFER_COMPLETE) {
      string name;
      switch (complete) {
        case GL_FRAMEBUFFER_UNDEFINED:
          name = "GL_FRAMEBUFFER_UNDEFINED";
          break;

        case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:
          name = "GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT";
          break;

        case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:
          name = "GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT";
          break;

        case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER :
          name = "GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER";
          break;

        case GL_FRAMEBUFFER_UNSUPPORTED:
          name = "GL_FRAMEBUFFER_UNSUPPORTED";
          break;

        case GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE:
          name = "GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER";
          break;

        case GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS:
          name = "GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS";
          break;

        default:
          name = to_string(complete);
      }
      throw runtime_error("Framebuffer is incomplete: " + name);
    }
  }

  void Frame_Buffer::attach_texture(texturing::Texture *texture) {
    glFramebufferTexture2D(
      GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, (GLenum) texture->get_mode(), texture->get_id(), 0);
//    glFramebufferTexture(GL_DRAW_BUFFER, GL_COLOR_ATTACHMENT0, texture->get_id(), 0);
//    auto color = glm::vec4(0);
//    glClearBufferiv(GL_FRAMEBUFFER, id, (GLint*)&color);
    auto clear_color = glow::get_clear_color();
    glow::set_clear_color(vec4(0));
    glClear(GL_COLOR_BUFFER_BIT);
    glow::set_clear_color(clear_color);
    check_complete();
  }

}