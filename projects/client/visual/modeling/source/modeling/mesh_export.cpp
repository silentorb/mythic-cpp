#include "mesh_export.h"

namespace modeling {
  namespace mesh_export {

    int get_vertex_count(const Basic_Mesh &mesh) {
      int result = 0;
      for (auto polygon: mesh.polygons) {
        result += polygon->vertices.size();
      }
      return result;
    }

    int get_attribute_id(const string &name) {
      if (name == "normal")
        return Vertex_Data::normal;

      if (name == "color")
        return Vertex_Data::color;

      throw runtime_error("Unknown vertex attribute name: " + name);
    }

    void output(const Basic_Mesh &mesh, Vertex_Schema &vertex_schema, Mesh_Export &result) {
      auto vertex_count = get_vertex_count(mesh);
      auto vertices = new float[vertex_count * vertex_schema.get_vertex_size()];
      auto offsets = new int[mesh.polygons.size()];
      auto counts = new int[mesh.polygons.size()];
      float *value = &vertices[0];
      int *offset_pointer = &offsets[0];
      int *count_pointer = &counts[0];
      int offset = 0;
      bool has_opacity = false;

      for (auto polygon: mesh.polygons) {
        for (int j = 0; j < polygon->vertices.size(); ++j) {
          auto vertex = polygon->vertices[j];
          *((vec3 *) value) = vertex->get_position();
          value += 3;
          for (int i = 1; i < vertex_schema.get_attribute_count(); ++i) {
            auto &attribute = vertex_schema.get_attribute(i);
            float *data = polygon->get_data(attribute.get_id(), j);
            if (!data) {
              value += attribute.get_count();
              continue;
            }

            if (attribute.get_name() == "color" && *(data + 3) != 1) {
              has_opacity = true;
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

      result.initialize(
        mesh.polygons.size(),
        vertex_count,
        vertices,
        offsets,
        counts,
        has_opacity
      );
    }

    Mesh_Data *output(const Basic_Mesh &mesh, Vertex_Schema &vertex_schema, bool support_lines) {
      Mesh_Export cache;
      output(mesh, vertex_schema, cache);

      return new Mesh_Data([=](Mesh_Export &result) {
        result = cache;
      }, vertex_schema, support_lines);
    }
  }
}
