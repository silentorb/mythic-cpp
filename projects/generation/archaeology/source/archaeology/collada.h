#pragma once


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
  unique_ptr<sculptor_old::geometry::Basic_Mesh> load_collada_file(const string filename);
  void load_collada_file(const string filename, Mesh_Delegate delegate, bool load_materials = true);
}