#pragma once

#include "dllexport.h"
#include "geometry/Mesh.h"
#include <string>
#include <math/utility.h>

using namespace sculptor::geometry;
using namespace std;

namespace sculptor {
  namespace operations {

    MYTHIC_EXPORT void flatten_normals(Mesh &mesh);

    MYTHIC_EXPORT void set_mesh_data(geometry::Mesh &mesh, const string &attribute_name, float *values, int count);

    MYTHIC_EXPORT void circle_vertices(vec3 *points, int point_count, float radius, float degrees = M_PI * 2);

    MYTHIC_EXPORT void transform(vec3 *points, mat4 matrix, int count);

    MYTHIC_EXPORT Mesh *lathe(vec3 *vertices, int point_count, float degrees = M_PI * 2);

    vec3 transform(vec3 point, mat4 matrix);
  }
}