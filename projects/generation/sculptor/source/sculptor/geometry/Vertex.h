#pragma once

namespace sculptor {
  namespace geometry {
    class Vertex {
    public:
        Vertex(vec3 tvec3);
        vector<Mesh*> meshes;
        vector<Polygon*> polygons;
        vector<Edge*> edges;
    };
  }
}