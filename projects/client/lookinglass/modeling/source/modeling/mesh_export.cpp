#include "mesh_export.h"
#include "Textured_Vertex.h"
#include <memory>

namespace modeling {
  namespace mesh_export {

    int get_vertex_count(Mesh &mesh) {
      int result = 0;
      for (auto polygon: mesh.polygons) {
        result += polygon->vertices.size();
      }
      return result;
    }

    Mesh_Data *output(Mesh &mesh, Vertex_Schema &vertex_schema) {
      auto vertex_count = get_vertex_count(mesh);
      auto vertices = new float[vertex_count * vertex_schema.get_vertex_size()];
      auto offsets = new int[mesh.polygons.size()];
      auto counts = new int[mesh.polygons.size()];
      float *value = &vertices[0];
      int *offset_pointer = &offsets[0];
      int *count_pointer = &counts[0];
      int offset = 0;

      for (auto polygon: mesh.polygons) {
        for (int j = 0; j < polygon->vertices.size(); ++j) {
          auto source = polygon->vertices[j];
          vec3 *position = (vec3 *) value;
          *position = source->get_position();
          value += 3;
          for (int i = 1; i < vertex_schema.get_attribute_count(); ++i) {
            auto &attribute = vertex_schema.get_attribute(i);
            float *data = polygon->get_data(attribute.get_name(), j);
            if (!data) {
              value += attribute.get_count();
              continue;
            }

            for (int k = 0; k < attribute.get_count(); ++k) {
              *value++ = *data++;
            }
          }
        }

        *offset_pointer++ = offset;
        offset += polygon->vertices.size();

        *count_pointer++ = polygon->vertices.size();
      }

      return new Mesh_Data(
        mesh.polygons.size(),
        vertex_count,
        vertices,
        offsets,
        counts,
        vertex_schema
      );
    }
  }
}
