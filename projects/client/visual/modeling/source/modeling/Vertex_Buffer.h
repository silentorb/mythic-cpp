#pragma once

#include "resourceful/Resource.h"
#include "shading/Vertex_Schema.h"
#include <functional>

using namespace std;
using namespace shading;

namespace modeling {

  typedef function<float *(int &)> Vertex_Generator;

  class Vertex_Buffer : public resourceful::Resource {
      unsigned int vbo = 0;
      unsigned int vao = 0;
      const Vertex_Schema &vertex_schema;
      Vertex_Generator generator;
      bool is_dynamic = false;
      int vertex_count = 0;

      void initialize();

  public:
      Vertex_Buffer(const Vertex_Schema &vertex_schema, Vertex_Generator generator = nullptr);

      ~Vertex_Buffer();

      virtual void load() override;
      void load(int new_vertex_count, float *data);

      virtual void release() override;

      void activate();

      const Vertex_Schema &get_vertex_schema() const {
        return vertex_schema;
      }

      void draw_points(int count);

      int get_vertex_count() const {
        return vertex_count;
      }
  };
}