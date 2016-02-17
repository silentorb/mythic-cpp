#include <sculptor/operations/extrude.h>
#include <glm/gtx/transform.hpp>
#include "create.h"

using namespace glm;

namespace sculptor {
  namespace create {

    Mesh *box(vec3 size) {
      auto half = size * 0.5f;
      auto mesh = new Mesh();
      Polygon *polygon = mesh->add_polygon(
        vec3(-half.x, half.y, half.z),
        vec3(half.x, half.y, half.z),
        vec3(half.x, -half.y, half.z),
        vec3(-half.x, -half.y, half.z)
      );
      polygon->set_normal(vec3(0, 0, 1));

      auto transform = glm::translate(vec3(0, 0, -size.z));
      sculptor::operations::extrude(mesh->get_edges(), transform, true);
      return mesh;
    }
  }
}