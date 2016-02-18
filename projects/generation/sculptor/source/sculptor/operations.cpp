#include <glm/gtx/euler_angles.hpp>
#include "operations.h"
#include "geometry/Polygon.h"
#include "geometry/Vertex.h"

namespace sculptor {
  using namespace geometry;

  namespace operations {

    void flatten_normals(Mesh &mesh) {
      for (auto &polygon: mesh.polygons) {
        auto normal = polygon->get_normal();
        polygon->set_data("normal", (float *) &normal, 3);
      }
    }

    void set_mesh_data(Mesh &mesh, const string &attribute_name, float *values, int count) {
      for (auto &polygon: mesh.polygons) {
        polygon->set_data(attribute_name, values, count);
      }
    }

    void circle_vertices(vec3 *points, int point_count, float radius, float degrees) {
      auto resolution = point_count;
      if (degrees != M_PI * 2)
        resolution -= 1;

      auto point_theta = -degrees / resolution;

      for (int i = 0; i < point_count; i++) {
        auto theta = point_theta * i;
        auto x = -sin(theta) * radius;
        auto y = cos(theta) * radius;
        points[i] = vec3(x, y, 0);
      }
    }

    MYTHIC_EXPORT void transform(vec3 *points, mat4 matrix, int count) {
      for (int i = 0; i < count; ++i) {
        points[i] = transform(points[i], matrix);
      }
    }

    template<typename T>
    T **get_slice(T **points, int start, int end) {
      auto count = end - start;
      auto result = new T *[count];
      memcpy(result, points + start, count * sizeof(T *));
      return result;
    }

    Vertex **clone(Vertex **source, mat4 &offset, int count) {
      if (count == 0)
        return nullptr;

      auto mesh = source[0]->meshes[0];
      auto result = new Vertex *[count];
      for (int i = 0; i < count; i++) {
        auto new_vector = transform(source[i]->get_position(), offset);
        result[i] = mesh->add_vertex(new_vector);
      }

      return result;
    }

    Mesh *lathe(vec3 *vertices, int vertical_count, int point_count, float degrees) {
      auto mesh = new Mesh();
      mesh->add_vertices(vertices, vertical_count);
      auto &first = mesh->get_vertex(0);
      auto &last = mesh->get_vertex(mesh->get_vertex_count() - 1);
//      auto previous = mesh->vertices.Skip(1).Take(vertices.Length - 2).ToArray();
      auto previous = get_slice(mesh->get_vertex_data(), 1, vertical_count - 2);
      int previous_count = vertical_count - 3;
      auto rotation = glm::eulerAngleZ(degrees / point_count);

      for (int i = 0; i < point_count; i++) {
        auto next = clone(previous, rotation, previous_count);
        mesh->add_polygon({
                            &first,
                            previous[0],
                            next[0],
                          });

        for (int j = 0; j < previous_count - 1; j++) {
          mesh->add_polygon({
                              previous[j + 1],
                              next[j + 1],
                              next[j],
                              previous[j],
                            });
        }

        mesh->add_polygon({
                            next[previous_count - 1],
                            previous[previous_count - 1],
                            &last,
                          });

        previous = next;
      }

      return mesh;
    }

    vec3 transform(const vec3 point, const mat4 matrix) {
      return vec3(matrix * vec4(point, 1));
    }
  }
}