#pragma once

namespace sculptor {
  namespace geometry {
    class Edge {
        vector<Mesh *> meshes;
        vector<Vertex *> vertices;
        vector<Polygon *> polygons;
    };
  }
}