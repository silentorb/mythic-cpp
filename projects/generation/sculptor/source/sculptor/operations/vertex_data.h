#pragma once

#include "dllexport.h"
#include <string>
#include <sculptor/geometry/Mesh.h>

using namespace std;
namespace sculptor {

  MYTHIC_EXPORT void set_mesh_data(geometry::Mesh &mesh, const string &attribute_name, float *values, int count);
}