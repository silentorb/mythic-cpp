#pragma once

#include "dllexport.h"
#include "resourceful/Resource.h"

namespace modeling {

  class Vertex_Schema;

  class MYTHIC_EXPORT Simple_Mesh : public resourceful::Resource {
      unsigned int vao;
      unsigned int vbo;
      int vertex_count;
      float *data;
      const Vertex_Schema &vertex_schema;

  public:
      Simple_Mesh(float *data, int vertex_count, const Vertex_Schema &vertex_schema);
      Simple_Mesh(const Vertex_Schema &vertex_schema);
      ~Simple_Mesh();
      void render();

      // Only needed for dynamic meshes
      void load(float *data, int vertex_count);

      virtual void load() override;
      virtual void free() override;
  };
}