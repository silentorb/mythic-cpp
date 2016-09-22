#include "Overlap_Clip.h"
#include <perspective/Viewport.h>
#include <bloom/Garden.h>
#include <glow.h>
#include <glow_gl.h>

using namespace perspective;

namespace bloom {
  namespace flowers {

    void Overlap_Clip::render() {
      auto previous_viewport = Viewport::get_active_viewport();
      auto &converter = Garden::get_instance().get_converter();
      auto pos_y = converter.get_pixel_dimensions().y - bounds.position.y - bounds.dimensions.y;
//  auto dimensions = glm::ivec2(bounds.dimensions) * glm::ivec2(converter.get_pixel_dimensions()) /previous_viewport->get_dimensions();
      auto dimensions = glm::ivec2(bounds.dimensions);
//  Viewport viewport(*previous_viewport, dimensions,
//                    glm::ivec2(bounds.position.x, pos_y) + previous_viewport->get_position());
      glScissor(
        bounds.position.x + previous_viewport->get_position().x,
        pos_y + previous_viewport->get_position().y,
        dimensions.x,
        dimensions.y
      );
      glEnable(GL_SCISSOR_TEST);
//  Viewport viewport(*previous_viewport,
//                    glm::ivec2(previous_viewport->get_dimensions().x * 0.8, previous_viewport->get_dimensions().y),
//                    previous_viewport->get_position());
//  viewport.activate();
      flowers::Single_Parent::render();
      glDisable(GL_SCISSOR_TEST);
//  previous_viewport->activate();
    }

    Overlap_Clip::~Overlap_Clip() {

    }

    vec2 Overlap_Clip::update_dimensions(const glm::vec2 &parent_dimensions) {
      bounds.dimensions = parent_dimensions;
      return Single_Parent::update_dimensions(parent_dimensions);
    }

    void Overlap_Clip::update_position(const glm::vec2 &parent_position, const glm::vec2 &parent_dimensions) {
      bounds.position = parent_position;
      Single_Parent::update_position(parent_position, parent_dimensions);
    }
  }
}