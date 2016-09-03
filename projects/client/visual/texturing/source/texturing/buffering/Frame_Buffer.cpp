#include "Frame_Buffer.h"
#include <glow_gl.h>
#include <glow.h>
#include <resourceful/Resource_Handler.h>
#include <glm/vec4.hpp>
#include "Render_Buffer.h"

using namespace resourceful;
using namespace std;
using namespace texturing;
using namespace glm;

namespace texturing {
  namespace buffering {

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

    void Frame_Buffer::set_read() {
      glBindFramebuffer(GL_READ_FRAMEBUFFER, id);
      glReadBuffer(GL_COLOR_ATTACHMENT0);
    }

    void Frame_Buffer::set_draw() {
      glBindFramebuffer(GL_DRAW_FRAMEBUFFER, id);
      if (attachments.size() > 0) {
        GLenum frame_buffers[2];
        GLenum k = GL_COLOR_ATTACHMENT0;
        for (int i = 0; i < attachments.size(); ++i) {
          frame_buffers[i] = attachments[i].port;
          glFramebufferRenderbuffer(GL_DRAW_FRAMEBUFFER, attachments[i].port, GL_RENDERBUFFER, attachments[i].render_buffer->get_id());
        }
        glDrawBuffers(attachments.size(), frame_buffers);
      }
      else {
        GLenum frame_buffers[] = {GL_COLOR_ATTACHMENT0};
        glDrawBuffers(1, frame_buffers);
      }
//      glDrawBuffer(GL_FRAMEBUFFER);
//      check_complete();
    }

    void Frame_Buffer::deactivate() {
      // Probably don't need to unbind this but I'm doing it for now until the code is more battle-tested.
      glBindFramebuffer(GL_FRAMEBUFFER, 0);
      GLenum frame_buffers = {GL_BACK};
      glDrawBuffers(1, &frame_buffers);
      glow::check_error("checking");
//    glDrawBuffer(GL_BACK);
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

#ifdef GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER
          case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER :
            name = "GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER";
            break;
#endif

          case GL_FRAMEBUFFER_UNSUPPORTED:
            name = "GL_FRAMEBUFFER_UNSUPPORTED";
            break;

          case GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE:
            name = "GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER";
            break;

#ifdef GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS
          case GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS:
            name = "GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS";
            break;
#endif

          default:
            name = to_string(complete);
        }
        throw runtime_error("Framebuffer is incomplete: " + name);
      }
    }

    void Frame_Buffer::attach_texture(texturing::Texture *texture) {
      glBindFramebuffer(GL_FRAMEBUFFER, id);
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
      glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    void Frame_Buffer::attach_render_buffer(const shared_ptr<Render_Buffer> &render_buffer, GLenum port) {
      attachments.push_back({render_buffer, port});
      glBindFramebuffer(GL_DRAW_FRAMEBUFFER, id);
      glFramebufferRenderbuffer(GL_DRAW_FRAMEBUFFER, port, GL_RENDERBUFFER, render_buffer->get_id());
    }
  }
}