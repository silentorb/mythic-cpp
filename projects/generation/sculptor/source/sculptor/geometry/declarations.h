#pragma once
#include "dllexport.h"

#include "glm/glm.hpp"
#include <vector>
#include <memory>
#include "dllexport.h"

using namespace std;
using namespace glm;

namespace sculptor {
  namespace geometry {

    class MYTHIC_EXPORT Mesh;

    class MYTHIC_EXPORT Vertex;

    class MYTHIC_EXPORT Polygon;

    class MYTHIC_EXPORT Edge;

    typedef shared_ptr<Mesh> Mesh_Pointer;
    typedef shared_ptr<Vertex> Vertex_Pointer;
    typedef shared_ptr<Polygon> Polygon_Pointer;
    typedef shared_ptr<Edge> Edge_Pointer;

  }
}