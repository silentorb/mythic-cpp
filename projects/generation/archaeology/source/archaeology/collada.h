#pragma once

#include "dllexport.h"
#include <string>
#include <memory>

namespace sculptor {
  namespace geometry {
    class Mesh;
  }
}

using namespace std;

namespace archaeology {
  MYTHIC_EXPORT unique_ptr<sculptor::geometry::Mesh> load_collada_file(const string filename);
}