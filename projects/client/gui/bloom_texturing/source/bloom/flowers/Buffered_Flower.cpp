#include "Buffered_Flower.h"
#include <texturing/Frame_Buffer.h>
#include <glow_gl.h>
#include <glow.h>
#include <lookinglass/House.h>
#include <perspective/Viewport.h>

using namespace texturing;

namespace bloom {
  namespace flowers {

    Buffered_Flower::Buffered_Flower(const Buffered_Flower_Renderer &renderer) :
      renderer(renderer) {
      frame_buffer = shared_ptr<Frame_Buffer>(new Frame_Buffer());
      auto &house = lookinglass::House::get_instance();
      house.watch_resource(frame_buffer);
    }

    void Buffered_Flower::prepare_texture() {
      auto dimensions = get_absolute_bounds().dimensions;
      if (!texture) {
        auto &house = lookinglass::House::get_instance();
        texture = shared_ptr<Texture>(new Texture(dimensions, nullptr, (char) house.get_options().get_multisampling()));
        house.watch_resource(texture);
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
      frame_buffer->activate();
      frame_buffer->attach_texture(texture.get());
      auto &house = lookinglass::House::get_instance();
      auto &base_viewport = house.get_base_viewport();
      perspective::Viewport viewport(house.get_viewport_mist(), base_viewport.get_width(), base_viewport.get_height(),
                                     -bounds.position.x, bounds.position.y);
      viewport.activate();
      flowers::Single_Parent::render();
      base_viewport.activate();
      texturing::Frame_Buffer::deactivate();
      renderer(bounds.position, bounds.dimensions, *texture);
    }
  }
}