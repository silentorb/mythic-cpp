#pragma once

#include "dllexport.h"
#include <string>
#include <memory>

namespace sculptor {
  namespace geometry {
    class Basic_Mesh;
  }
}

using namespace std;

namespace archaeology {
  MYTHIC_EXPORT unique_ptr<sculptor::geometry::Basic_Mesh> load_collada_file(const string filename);
}