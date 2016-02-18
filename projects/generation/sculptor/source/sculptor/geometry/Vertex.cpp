#include <vectoring/utility.h>
#include "sculptor/geometry.h"

namespace sculptor {
  namespace geometry {

    Vertex::Vertex(vec3 vector)
      : position(vector) {
    }

    Vertex::~Vertex() {

    }

    template<typename Iterator>
    Vertex::Vertex(vec3 vector, Iterator new_meshes)
      : position(vector) {
      for (auto mesh: new_meshes) {
        mesh.add_vertex(this);
      }
    }

    Edge *Vertex::get_edge(Vertex *other) {
      for (auto edge: edges) {
        if (edge->contains(other))
          return edge;
      }

      return NULL;
    }
  }
}