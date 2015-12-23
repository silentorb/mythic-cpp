#pragma once

namespace sculptor {
  namespace geometry {
    class Edge {
    public:
        Edge(Vertex *first, Vertex *second);
        vector<Mesh *> meshes;
        Vertex * vertices[2];
        vector<Polygon *> polygons;
        bool contains(Vertex *vertex);
        void get_ordered_points(Vertex* points[2]);
    };
  }
}