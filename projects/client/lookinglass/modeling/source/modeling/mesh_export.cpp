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

    Mesh_Data *output_textured(Mesh &mesh) {
      const auto vertex_schema = new Vertex_Schema({3, 3, 2});
      auto vertex_count = get_vertex_count(mesh);
      auto vertices = new Textured_Vertex[vertex_count];
      auto offsets = new int[mesh.polygons.size()];
      auto counts = new int[mesh.polygons.size()];
      Textured_Vertex *vertex = &vertices[0];
      int *offset_pointer = &offsets[0];
      int *count_pointer = &counts[0];
      int offset = 0;

      for (auto polygon: mesh.polygons) {
        for (int j = 0; j < polygon->vertices.size(); ++j) {
          auto source = polygon->vertices[j];
          vertex->position = source->position;
          vertex->normal = glm::normalize(source->position);
          if (polygon->uvs) {

          }
          ++vertex;
        }

        *offset_pointer++ = offset;
        offset += polygon->vertices.size();

        *count_pointer++ = polygon->vertices.size();
      }

      return new Mesh_Data(
        mesh.polygons.size(),
        vertex_count,
        (float *) vertices,
        offsets,
        counts,
        std::shared_ptr<Vertex_Schema>(vertex_schema)
      );
    }
  }
}
