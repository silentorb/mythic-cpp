#include "Graph.h"
#include <modeling/Simple_Mesh.h>
#include <drawing/Draw.h>
#include <bloom/Garden.h>
#include <glow_gl.h>

namespace bloom {
  namespace graphing {

    Graph::Graph() :
      mesh(new modeling::Simple_Mesh(drawing::Draw::get_instance().get_solid_vertex_schema())) {

    }

    void Graph::initialize_colored_points() {
      colored_points.reserve(points.size());
      auto min = points[0].x;
      auto max = points[points.size() - 1].x;
      float padding = 0.1f;
      auto horizontal_scale = (1 - padding * 2) / (max - min);
      for (auto &point : points) {
        colored_points.emplace_back(vec2{padding + point.x * horizontal_scale, point.y}, glm::vec4(1));
      }

      mesh->replace((float*)colored_points.data(), colored_points.size());
    }

    void Graph::render() {
      flowers::Common_Flower::render();
      auto& draw = drawing::Draw::get_instance();
      auto bounds = parent->get_absolute_bounds();
      auto &converter = Garden::get_instance().get_converter();

      auto &effect = draw.get_square_effect();
      effect.activate();
      effect.set_color(vec4(1));

      draw.draw_square(converter.convert_to_units(bounds.position.x),
                       converter.convert_to_units(bounds.position.y),
                       converter.convert_to_units(bounds.dimensions.x),
                       converter.convert_to_units(bounds.dimensions.y),
                       modeling::Draw_Method::line_strip, effect, *mesh);

      glPointSize(10);
      draw.draw_square(converter.convert_to_units(bounds.position.x),
                       converter.convert_to_units(bounds.position.y),
                       converter.convert_to_units(bounds.dimensions.x),
                       converter.convert_to_units(bounds.dimensions.y),
                       modeling::Draw_Method::points, effect, *mesh);
    }
  }
}