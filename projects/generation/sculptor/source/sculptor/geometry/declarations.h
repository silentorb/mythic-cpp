#pragma once

#include "commoner/dllexport.h"

#include "glm/glm.hpp"
#include <vector>
#include <memory>
#include "commoner/dllexport.h"

using namespace std;
using namespace glm;

namespace sculptor {
  namespace geometry {

    class Basic_Mesh;

    class Vertex;

    class Polygon;

    class Edge;

    typedef shared_ptr<Basic_Mesh> Mesh_Pointer;
    typedef shared_ptr<Vertex> Vertex_Pointer;
    typedef shared_ptr<Polygon> Polygon_Pointer;
    typedef shared_ptr<Edge> Edge_Pointer;

    MYTHIC_EXPORT typedef vector<Edge *> Edge_List;
  }
}