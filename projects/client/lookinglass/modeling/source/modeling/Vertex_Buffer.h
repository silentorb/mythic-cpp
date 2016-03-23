#pragma once

#include "resourceful/Resource.h"
#include "shading/Vertex_Schema.h"
#include <functional>

using namespace std;
using namespace shading;

namespace modeling {

  typedef function<float *(int &)> Vertex_Generator;

  class MYTHIC_EXPORT Vertex_Buffer : public resourceful::Resource {
      unsigned int vbo = 0;
      unsigned int vao = 0;
      const Vertex_Schema &vertex_schema;
      Vertex_Generator generator;

  public:
      Vertex_Buffer(const Vertex_Schema &vertex_schema, Vertex_Generator generator = nullptr);

      ~Vertex_Buffer();

//      const unsigned int &get_vao() const {
//        return vao;
//      }

      virtual void load() override;
      void load(int vertex_count, float *data);

      virtual void free() override;

      void activate();

      const Vertex_Schema &get_vertex_schema() const {
        return vertex_schema;
      }

      void draw_points(int count);
  };
}