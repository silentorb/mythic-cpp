#pragma once


#include "Vertex_Schema.h"

namespace lookinglass {
  namespace modeling {

    class Mesh_Data {
    private:
        unsigned int vao;
        unsigned int vbo;
        int polygon_count;
        int vertex_count;
        float *vertices;
        int *offsets;
        int *counts;
        void register_mesh(const Vertex_Schema &schema);

    public:

        Mesh_Data(int polygon_count, int vertex_count, float *vertices, int *offsets, int *counts,
                  const Vertex_Schema &vertex_schema);

        ~Mesh_Data();

        unsigned int get_vao() const {
          return vao;
        }

        int get_polygon_count() const {
          return polygon_count;
        }

        int get_vertex_count() const {
          return vertex_count;
        }

        float *get_vertices() const {
          return vertices;
        }

        int *get_offsets() const {
          return offsets;
        }

        int *get_counts() const {
          return counts;
        }
    };

  }
}