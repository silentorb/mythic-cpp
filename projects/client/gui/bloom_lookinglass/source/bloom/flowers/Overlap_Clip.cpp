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
      auto dimensions = glm::ivec2(get_absolute_bounds().dimensions);
      auto pos_y = converter.get_pixel_dimensions().y - bounds.position.y - dimensions.y;

      glScissor(
        (int)bounds.position.x + previous_viewport->get_position().x,
        (int)pos_y + previous_viewport->get_position().y,
        dimensions.x,
        dimensions.y
      );
      glEnable(GL_SCISSOR_TEST);

      flowers::Single_Parent::render();
      glDisable(GL_SCISSOR_TEST);
    }

    Overlap_Clip::~Overlap_Clip() {

    }

    vec2 Overlap_Clip::update_dimensions(const glm::vec2 &parent_dimensions) {
//      bounds.dimensions = parent_dimensions;
//      if (parent_dimensions.x == 0) {
//        bounds.dimensions.x =parent->get_absolute_bounds().dimensions.x;
//      }
//      if (parent_dimensions.y == 0) {
//        bounds.dimensions.y =parent->get_absolute_bounds().dimensions.y;
//      }
      return bounds.dimensions = Single_Parent::update_dimensions(parent_dimensions);
    }

    void Overlap_Clip::update_position(const glm::vec2 &parent_position, const glm::vec2 &parent_dimensions) {
      bounds.position = parent_position;
      Single_Parent::update_position(parent_position, parent_dimensions);
    }

    const string Overlap_Clip::get_class_name() const {
      return "Overlap_Clip";
    }
  }
}