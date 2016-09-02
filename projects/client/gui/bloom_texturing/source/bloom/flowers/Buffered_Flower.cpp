#include "Buffered_Flower.h"
#include <bloom/Garden.h>
#include <glow_gl.h>
#include <glow.h>
#include <lookinglass/House.h>
#include <perspective/Viewport.h>
#include <glow/Capabilities.h>
#include <texturing/buffering/Render_Buffer.h>
#include <texturing/buffering/Frame_Buffer.h>

using namespace texturing;
using namespace texturing::buffering;

namespace bloom {
  namespace flowers {

    Buffered_Flower::Buffered_Flower(const Buffered_Flower_Renderer &renderer) :
      renderer(renderer) {
      auto &house = lookinglass::House::get_instance();
      multisamples = house.get_capabilities().multisamplers()
                     ? house.get_options().get_multisampling()
                     : 0;

      frame_buffer = shared_ptr<Frame_Buffer>(new Frame_Buffer());
      house.watch_resource(frame_buffer);
      if (multisamples) {
        multisample_frame_buffer = shared_ptr<Frame_Buffer>(new buffering::Frame_Buffer());
        house.watch_resource(multisample_frame_buffer);
      }
    }

    void Buffered_Flower::prepare_texture() {
      auto dimensions = get_absolute_bounds().dimensions;
      if (!texture) {
        auto &house = lookinglass::House::get_instance();
        texture = shared_ptr<Texture>(new Texture(dimensions, nullptr, 0));
        house.watch_resource(texture);
//        if (multisamples) {
//          multisample_texture = shared_ptr<Texture>(new Texture(dimensions, nullptr, (char) multisamples));
//          house.watch_resource(multisample_texture);
//        }

        if (multisamples) {
          multisample_render_buffer = shared_ptr<Render_Buffer>(new buffering::Render_Buffer(dimensions, multisamples));
          house.watch_resource(multisample_render_buffer);
        }
      }
      else if (texture->get_dimensions() != glm::ivec2(dimensions)) {
        throw runtime_error("Not yet implemented.");
      }
    }

//    void Buffered_Flower::update_position(const glm::vec2 &parent_position, const glm::vec2 &parent_dimensions) {
//      flowers::Single_Parent::update_position(glm::vec2(), parent_dimensions);
//    }

    void Buffered_Flower::render() {
      auto &bounds = get_absolute_bounds();
      prepare_texture();

      if (multisamples) {
        multisample_frame_buffer->activate();
        multisample_frame_buffer->attach_render_buffer(multisample_render_buffer.get());
        auto color = glm::vec4(0);
//        glClearBufferiv(GL_FRAMEBUFFER, multisample_frame_buffer->get_id(), (GLint*)&color);
        auto clear_color = glow::get_clear_color();
        glow::set_clear_color(vec4(0));
        glClear(GL_COLOR_BUFFER_BIT);
        glow::set_clear_color(clear_color);
//        multisample_render_buffer->activate();
      }
      else {
        frame_buffer->activate();
        frame_buffer->attach_texture(texture.get());
      }
      auto &house = lookinglass::House::get_instance();
      auto &base_viewport = house.get_base_viewport();
      auto &converter = Garden::get_instance().get_converter();
      auto pos_y = converter.get_pixel_dimensions().y - bounds.position.y - bounds.dimensions.y;
      perspective::Viewport viewport(house.get_viewport_mist(), base_viewport.get_width(), base_viewport.get_height(),
                                     -bounds.position.x, pos_y);
      viewport.activate();
      flowers::Single_Parent::render();
      base_viewport.activate();
      if (multisamples) {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glBindFramebuffer(GL_DRAW_FRAMEBUFFER, frame_buffer->get_id());
        frame_buffer->attach_texture(texture.get());

        glBindFramebuffer(GL_READ_FRAMEBUFFER, multisample_frame_buffer->get_id());
        GLenum frame_buffers = {GL_COLOR_ATTACHMENT0};
        glDrawBuffers(1, &frame_buffers);
//        glDrawBuffer(GL_COLOR_ATTACHMENT0);
        glReadBuffer(GL_COLOR_ATTACHMENT0);
//        glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);   // Make sure no FBO is set as the draw framebuffer
//        glBindFramebuffer(GL_READ_FRAMEBUFFER, multisample_frame_buffer->get_id()); // Make sure your multisampled FBO is the read framebuffer
//        glDrawBuffer(GL_BACK);
        //bounds.position.x, bounds.position.y
        glBlitFramebuffer(0, 0, bounds.dimensions.x, bounds.dimensions.y, 0, 0, bounds.dimensions.x,
                          bounds.dimensions.y,
                          GL_COLOR_BUFFER_BIT, GL_NEAREST);
      }
      Frame_Buffer::deactivate();
      renderer(bounds.position, bounds.dimensions, *texture);
    }
  }
}