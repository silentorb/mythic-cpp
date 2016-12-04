#pragma once

#include "Simple_Mesh.h"
#include "Index_Source.h"
#include "Vertex_Buffer.h"
#include "Element_Buffer.h"

namespace modeling {

  class Indexed_Mesh {
      Vertex_Buffer vertex_buffer;
      Element_Buffer element_buffer;

  public:
      Indexed_Mesh(const Vertex_Schema &vertex_schema);
      virtual void render(Draw_Method mode);
  };
}