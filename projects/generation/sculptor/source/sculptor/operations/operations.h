#pragma once


#include "sculptor/geometry/Mesh.h"
#include "selection.h"
#include <string>
#include <math/utility.h>

using namespace sculptor_old::geometry;
using namespace std;

namespace sculptor_old {
  namespace operations {

    vec3 calculate_normal(Vertex *vertex);
    void flatten_normals(Basic_Mesh &mesh);
    void smooth_normals(Basic_Mesh &mesh);

    void set_mesh_data(geometry::Basic_Mesh &mesh, int id, float *values, int count);

    void circle_vertices(vec3 *points, int point_count, float radius, float degrees = M_PI * 2);

    vec3 transform(const vec3 point, const mat4 matrix);
    void transform(vec3 *points, const mat4 matrix, int count);
    void transform(Vertex **vertices, const mat4 matrix, int count);
//    void transform(Mesh &mesh, const mat4 matrix);
    void transform(Selection &selection, const mat4 matrix);
    void move(Vertex &vertex, const vec3 offset);

    Basic_Mesh *lathe(vec3 *vertices, int vertical_count, int point_count, float degrees = M_PI * 2);
    void mirror(Selection &selection, bool fill);
    void fill_gap(Selection &first, Selection &second);

    void bevel(Selection &selection, const mat4 &offset);

  }
}