#pragma once



#include "glm/glm.hpp"
#include <vector>
#include <memory>


using namespace std;
using namespace glm;

namespace sculptor_old {
  namespace geometry {

    class Basic_Mesh;

    class Vertex;

    class Polygon;

    class Edge;

    typedef shared_ptr<Basic_Mesh> Mesh_Pointer;
    typedef shared_ptr<Vertex> Vertex_Pointer;
    typedef shared_ptr<Polygon> Polygon_Pointer;
    typedef shared_ptr<Edge> Edge_Pointer;

    typedef vector<Edge *> Edge_List;
  }
}