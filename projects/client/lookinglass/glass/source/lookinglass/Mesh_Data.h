#pragma once

namespace lookinglass {
  struct Mesh_Data {
      unsigned int vao;
      unsigned int vbo;
      int polygon_count;
      int vertex_count;
      float *vertices;
      int *offsets;
      int *counts;
  };
}