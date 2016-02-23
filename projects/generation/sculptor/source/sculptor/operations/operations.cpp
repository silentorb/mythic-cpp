#include <glm/gtx/euler_angles.hpp>
#include <glm/gtx/transform.hpp>
#include "operations.h"
#include "sculptor/geometry/Polygon.h"
#include "sculptor/geometry/Edge.h"

namespace sculptor {
  using namespace geometry;

  namespace operations {

    void flatten_normals(Mesh &mesh) {
      for (auto &polygon: mesh.polygons) {
        auto normal = polygon->calculate_normal();
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

    template<typename T>
    T **get_slice(T **points, int start, int end) {
      auto count = end - start;
      auto result = new T *[count];
      memcpy(result, points + start, count * sizeof(T *));
      return result;
    }

    Mesh *lathe(vec3 *vertices, int vertical_count, int point_count, float degrees) {
      auto mesh = new Mesh();
      mesh->add_vertices(vertices, vertical_count);
      auto &first = mesh->get_vertex(0);
      auto &last = mesh->get_vertex(mesh->get_vertex_count() - 1);
//      auto previous = mesh->vertices.Skip(1).Take(vertices.Length - 2).ToArray();
      auto previous = selecting::slice(mesh->select(), 1, vertical_count - 2);
      int previous_count = vertical_count - 3;
      auto rotation = glm::eulerAngleZ(degrees / point_count);

      for (int i = 0; i < point_count; i++) {
        auto next = selecting::clone(previous, rotation);
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

    void transform(vec3 *points, const mat4 matrix, int count) {
      for (int i = 0; i < count; ++i) {
        points[i] = transform(points[i], matrix);
      }
    }

    void transform(Vertex **vertices, const mat4 matrix, int count) {
      for (int i = 0; i < count; ++i) {
        Vertex *vertex = vertices[i];
        vertex->set_position(transform(vertex->get_position(), matrix));
      }
    }

    vec3 transform(const vec3 point, const mat4 matrix) {
      vec3 result = vec3(matrix * vec4(point, 1));
      const float max = 0.00001;
      if (result.x < max && result.x > -max) result.x = 0;
      if (result.y < max && result.y > -max) result.y = 0;
      if (result.z < max && result.z > -max) result.z = 0;
      return result;
    }

//    void transform(Mesh &mesh, const mat4 matrix) {
//      transform(mesh.get_vertex_data(), matrix, mesh.get_vertex_count());
//    }

    void transform(Selection &selection, const mat4 matrix) {
      for (int i = 0; i < selection.size(); ++i) {
        Vertex *vertex = selection[i];
        vertex->set_position(transform(vertex->get_position(), matrix));
      }
    }

    void move(Vertex &vertex, const vec3 offset) {
      vertex.set_position(vertex.get_position() + offset);
    }

    void mirror(Selection &selection, bool fill) {
      Mesh *mesh = selecting::get_mesh(selection);
      auto other = selecting::clone(selection, glm::scale(vec3(-1, 1, 1)));

      auto polygons = selecting::get_polygons(other);
      for (auto polygon: polygons) {
        polygon->flip();
      }

      if (fill) {
        fill_gap(selection, other);
      }
    }

    void fill_gap(Selection &first, Selection &second) {
      auto mesh = selecting::get_mesh(first);
      auto edges = selecting::get_edge_edges(first);
      for (auto edge: edges) {
        Vertex *points[2];
        edge->get_ordered_points(points);
        auto a = selecting::get_vertex_index(first, *points[0]);
        auto b = selecting::get_vertex_index(first, *points[1]);
        if (edge->vertices[0] != points[0]) {
          auto c = a;
          a = b;
          b = c;
        }
        mesh->add_polygon(
          points[1],
          points[0],
          second[a],
          second[b]
        );
      }
    }
/*
    void disconnect_edges(vector<Edge *> edges) {

    }
    */
/*
    void bevel(Selection &selection, const mat4 &offset) {
      Mesh *mesh = selecting::get_mesh(selection);
      auto edges = selecting::get_edge_edges(selection);
      for (auto edge: edges) {

      }

//      auto other = selecting::clone(selection, offset);

//      auto polygons = selecting::get_polygons(selection);
//      for (auto polygon: polygons) {
//        polygon->flip();
//      }

      fill_gap(selection, other);
    }
    */
  }
}