#include "Fill.h"
#include <drawing/Draw.h>
#include <bloom/flowers/Parent_Implementation.h>
#include "bloom/Garden.h"

namespace bloom {
  namespace flowers {

    Fill::Fill(const glm::vec4 &color, flowers::Parent *parent) :
      color(color), mesh(drawing::Draw::get_instance().get_solid_mesh()) {
      flowers::Parent_Implementation::initialize_child(this, parent);
    }

    Fill::Fill(const glm::vec4 &color, modeling::Simple_Mesh &mesh, flowers::Parent *parent) :
      color(color), mesh(mesh) {
      flowers::Parent_Implementation::initialize_child(this, parent);
    }

    void Fill::render() {
      auto& draw = drawing::Draw::get_instance();
      auto bounds = parent->get_absolute_bounds();
      auto &converter = Garden::get_instance().get_converter();

      auto &effect = draw.get_square_effect();
      effect.activate();
      effect.set_color(color);

      draw.draw_square(converter.convert_to_units(bounds.position.x),
                        converter.convert_to_units(bounds.position.y),
                        converter.convert_to_units(bounds.dimensions.x),
                        converter.convert_to_units(bounds.dimensions.y),
                        modeling::Draw_Method::triangle_fan, effect, mesh);
    }
  }

}