#include "Border.h"
#include <drawing/Draw.h>
#include "bloom/Garden.h"
#include <glow.h>

namespace bloom {
  namespace flowers {

    Border::Border(const glm::vec4 &color, float thickness, flowers::Parent *parent) :
      thickness(thickness), color(color), mesh(drawing:: Draw::get_instance().get_solid_mesh()) {
      flowers::Parent_Implementation::initialize_child(this, parent);
    }

    Border::Border(const glm::vec4 &color, float thickness, modeling::Simple_Mesh &mesh,
                   modeling::Draw_Method draw_method,
                   flowers::Parent *parent) :
      thickness(thickness), color(color), mesh(mesh), draw_method(draw_method) {
      flowers::Parent_Implementation::initialize_child(this, parent);

    }

    void Border::render() {
      auto &draw = drawing::Draw::get_instance();
      auto bounds = parent->get_absolute_bounds();
      auto &converter = Garden::get_instance().get_converter();

      auto &effect = draw.get_square_effect();
      effect.activate();
      effect.set_color(color);

      glow::set_line_thickness(thickness * Measurement::pixel_scale);
      draw.draw_square(converter.convert_to_units(bounds.position.x),
                        converter.convert_to_units(bounds.position.y),
                        converter.convert_to_units(bounds.dimensions.x),
                        converter.convert_to_units(bounds.dimensions.y),
                        draw_method, effect, mesh);
    }
  }

}