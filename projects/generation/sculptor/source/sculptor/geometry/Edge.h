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

        template<typename Iterator>
        static void get_vertices(Iterator &edges, vector<Vertex *> vertices);

        template<typename Iterator>
        static void get_polygons(Iterator &edges, vector<Polygon *> polygons);
    };
  }
}