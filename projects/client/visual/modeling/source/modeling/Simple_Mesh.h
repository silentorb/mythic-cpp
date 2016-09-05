#pragma once

#include "commoner/dllexport.h"
#include "resourceful/Resource.h"
#include "Draw_Method.h"
#include "Renderable_Mesh.h"

namespace shading {
  class Vertex_Schema;
}
using namespace shading;

namespace modeling {

  class MYTHIC_EXPORT Simple_Mesh : public resourceful::Resource, public Renderable_Mesh {
      unsigned int vao;
      unsigned int vbo;
      int vertex_count;
      float *data;
      const Vertex_Schema &vertex_schema;

  public:
      Simple_Mesh(float *data, int vertex_count, const Vertex_Schema &vertex_schema);
      Simple_Mesh(const Vertex_Schema &vertex_schema);
      ~Simple_Mesh();
      virtual void render(Draw_Method mode) override;

      // Only needed for dynamic meshes
      void load(float *data, int vertex_count);

      virtual void load() override;
      virtual void release() override;
  };
}