#include "Buffered_Flower.h"
#include <texturing/Frame_Buffer.h>
#include <glow_gl.h>
#include <glow.h>

namespace bloom {
  namespace flowers {

    void Buffered_Flower::prepare_frame_buffer() {
      auto dimensions = get_absolute_bounds().dimensions;
      if (!frame_buffer || frame_buffer->get_width() != dimensions.x || frame_buffer->get_height() != dimensions.y) {
        frame_buffer = new texturing::Frame_Buffer((int) dimensions.x, (int) dimensions.y, 0);
      }
    }

    void Buffered_Flower::update_position(const glm::vec2 &parent_position, const glm::vec2 &parent_dimensions) {
      Single_Parent::update_position(glm::vec2(), parent_dimensions);
    }

    void Buffered_Flower::render() {
      prepare_frame_buffer();
      frame_buffer->activate();
      Single_Parent::render();
      texturing::Frame_Buffer::deactivate();
    }
  }
}