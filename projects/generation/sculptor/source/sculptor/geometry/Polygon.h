#pragma once


namespace sculptor {
  namespace geometry {
    class Polygon {
    public:
        vector<Mesh *> meshes;
        vector<Vertex *> vertices;
        vector<Edge *> edges;

        template<typename Iterator>
        Polygon(Iterator vertices);
    };
  }
}