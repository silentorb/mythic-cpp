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

  class MYTHIC_EXPORT Simple_Mesh : public resourceful::Resource, public Renderable_Mesh_With_Opacity {
      unsigned int vao;
      unsigned int vbo;
      int vertex_count;
      float *data;
      const Vertex_Schema &vertex_schema;
      bool is_dynamic = false;

  public:
      Simple_Mesh(float *data, int vertex_count, const Vertex_Schema &vertex_schema);
      Simple_Mesh(const Vertex_Schema &vertex_schema);
      ~Simple_Mesh();
      virtual void render(Draw_Method mode) override;
      void initialize();

      // Only needed for dynamic meshes
      void replace(float *data, int vertex_count);

      virtual void load() override;
      virtual void release() override;

      virtual bool has_opacity() const override {
        return false;
      }
  };
}