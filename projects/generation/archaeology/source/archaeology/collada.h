#pragma once

#include "commoner/dllexport.h"
#include <string>
#include <memory>
#include <vector>
#include <functional>

namespace sculptor_old {
  namespace geometry {
    class Basic_Mesh;
  }
}

using namespace std;

namespace archaeology {
  typedef function<void(const string name, unique_ptr<sculptor_old::geometry::Basic_Mesh> &mesh)> Mesh_Delegate;
  MYTHIC_EXPORT unique_ptr<sculptor_old::geometry::Basic_Mesh> load_collada_file(const string filename);
  MYTHIC_EXPORT void load_collada_file(const string filename, Mesh_Delegate delegate, bool load_materials = true);
}