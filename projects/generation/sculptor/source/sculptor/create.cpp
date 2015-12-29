#include <sculptor/operations/extrude.h>
#include <glm/gtx/transform.hpp>
#include "create.h"

namespace sculptor {
  namespace create {

    Mesh *box(vec3 size) {
      auto half = size * 0.5f;
      auto mesh = new Mesh();
      mesh->add_polygon(
        vec3(-half.x, half.y, half.z),
        vec3(half.x, half.y, half.z),
        vec3(half.x, -half.y, half.z),
        vec3(-half.x, -half.y, half.z)
      );

      auto transform = glm::translate(vec3(0, 0, -size.z));
      sculptor::operations::extrude(mesh->get_edges(), transform, true);
      return mesh;
    }
  }
}