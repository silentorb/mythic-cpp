#include "Draw.h"
#include <modeling/Simple_Mesh.h>
#include "modeling/Vertex_Schema.h"

using namespace modeling;

namespace drawing {

  Draw::Draw() :
    solid_vertex_schema(new Vertex_Schema({2})),
    image_vertex_schema(new Vertex_Schema({4})) {
    float solid_vertices[] = {
      -1, -1,
      -1, 1,
      1, 1,
      1, -1,
    };

    float image_vertices[] = {
//      -1, -1, 0, 1,
//      -1, 1, 1, 1,
//      1, 1, 1, 0,
//      1, -1, 0, 0
                
      0, 0, 0, 0,
      1, 0, 1, 0,
      1, 1, 1, 1,
      0, 1, 0, 1
    };

    solid_mesh = unique_ptr<Simple_Mesh>(new Simple_Mesh(solid_vertices, 4, *solid_vertex_schema.get()));
    image_mesh = unique_ptr<Simple_Mesh>(new Simple_Mesh(image_vertices, 4, *image_vertex_schema.get()));
  }

  Draw::~Draw() { }
}