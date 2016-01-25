#pragma once

#include "dllexport.h"
#include <memory>

namespace modeling {
  class Simple_Mesh;

  class Vertex_Schema;
}

using namespace std;

namespace drawing {

  class MYTHIC_EXPORT Draw {
      unique_ptr<modeling::Vertex_Schema> solid_vertex_schema;
      unique_ptr<modeling::Simple_Mesh> solid_mesh;

      unique_ptr<modeling::Vertex_Schema> image_vertex_schema;
      unique_ptr<modeling::Simple_Mesh> image_mesh;
  public:
      Draw();


      modeling::Simple_Mesh &get_solid_mesh() const {
        return *solid_mesh;
      }

      modeling::Simple_Mesh &get_image_mesh() const {
        return *image_mesh;
      }
  };
}



