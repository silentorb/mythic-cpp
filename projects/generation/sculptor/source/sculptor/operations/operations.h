#pragma once

#include "dllexport.h"
#include "sculptor/geometry/Mesh.h"
#include "selection.h"
#include <string>
#include <math/utility.h>

using namespace sculptor::geometry;
using namespace std;

namespace sculptor {
  namespace operations {

    MYTHIC_EXPORT void flatten_normals(Mesh &mesh);
    MYTHIC_EXPORT void smooth_normals(Mesh &mesh);

    MYTHIC_EXPORT void set_mesh_data(geometry::Mesh &mesh, const string &attribute_name, float *values, int count);

    MYTHIC_EXPORT void circle_vertices(vec3 *points, int point_count, float radius, float degrees = M_PI * 2);

    vec3 transform(const vec3 point, const mat4 matrix);
    MYTHIC_EXPORT void transform(vec3 *points, const mat4 matrix, int count);
    MYTHIC_EXPORT void transform(Vertex **vertices, const mat4 matrix, int count);
//    MYTHIC_EXPORT void transform(Mesh &mesh, const mat4 matrix);
    MYTHIC_EXPORT void transform(Selection &selection, const mat4 matrix);
    MYTHIC_EXPORT void move(Vertex &vertex, const vec3 offset);

    MYTHIC_EXPORT Mesh *lathe(vec3 *vertices, int vertical_count, int point_count, float degrees = M_PI * 2);
    MYTHIC_EXPORT void mirror(Selection &selection, bool fill);
    MYTHIC_EXPORT void fill_gap(Selection &first, Selection &second);

   MYTHIC_EXPORT void bevel(Selection &selection, const mat4 &offset);

    }
}