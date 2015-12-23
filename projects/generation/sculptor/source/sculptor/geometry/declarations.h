#pragma once

#include "glm/glm.hpp"
#include <vector>
#include <memory>

using namespace std;
using namespace glm;

namespace sculptor {
  namespace geometry {

    class Mesh;

    class Vertex;

    class Polygon;

    class Edge;

    typedef shared_ptr<Mesh> Mesh_Pointer;
    typedef shared_ptr<Vertex> Vertex_Pointer;
    typedef shared_ptr<Polygon> Polygon_Pointer;
    typedef shared_ptr<Edge> Edge_Pointer;

  }
}