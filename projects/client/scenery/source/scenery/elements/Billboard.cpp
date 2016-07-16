#include <sculptor/geometry.h>
#include "Billboard.h"

using namespace modeling;

namespace scenery {

  namespace billboard_data {
    unique_ptr<Mesh_Data> billboard_mesh;
    unique_ptr<Vertex_Schema> vertex_schema;

    float vertices[] = {
      -0.5, 0, -0.5, 0, 0,
      -0.5, 0, 0.5, 0, 1,
      0.5, 0, 0.5, 1, 1,
      0.5, 0, -0.5, 1, 0
    };
    int offsets = 0;
    int counts = 4;
  }

  Mesh_Data *get_billboard_mesh() {
    if (!billboard_data::billboard_mesh) {
      billboard_data::vertex_schema = unique_ptr<Vertex_Schema>(
        new Vertex_Schema(
          {
            Vertex_Attribute(sculptor::geometry::Vertex_Data::position, "position", 3),
            Vertex_Attribute(sculptor::geometry::Vertex_Data::uv, "uv", 2)
          }));

//      new Mesh_Data(1, 4, (float *) &billboard_data::vertices, &billboard_data::offsets,
//                    &billboard_data::counts, *billboard_data::vertex_schema)
      billboard_data::billboard_mesh = unique_ptr<Mesh_Data>(
        new Mesh_Data([&](Mesh_Export &result) {
          result.initialize(1, 4, (float *) &billboard_data::vertices, &billboard_data::offsets,
                            &billboard_data::counts);
        }, *billboard_data::vertex_schema)
      );
    }

    return billboard_data::billboard_mesh.get();
  }
}