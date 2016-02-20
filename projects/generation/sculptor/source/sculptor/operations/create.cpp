#include <sculptor/operations/extrude.h>
#include <glm/gtx/transform.hpp>
#include "create.h"
#include "operations.h"
#include <glm/gtx/euler_angles.hpp>

using namespace glm;

namespace sculptor {
  namespace create {

    Mesh *square(vec2 size, float z) {
      auto half = size * 0.5f;
      auto mesh = new Mesh();
      Polygon *polygon = mesh->add_polygon(
//        vec3(-half.x, half.y, half.z),
//        vec3(half.x, half.y, half.z),
//        vec3(half.x, -half.y, half.z),
//        vec3(-half.x, -half.y, half.z)

        {vec3(-half.x, -half.y, z),
         vec3(half.x, -half.y, z),
         vec3(half.x, half.y, z),
         vec3(-half.x, half.y, z)
        }
      );
//      polygon->set_normal(vec3(0, 0, 1));
      return mesh;
    }

    Mesh *box(vec3 size) {
      auto half = size * 0.5f;
      auto mesh = square(vec2(size.x, size.y), half.z);
      auto transform = glm::translate(vec3(0, 0, -size.z));
      operations::extrude(mesh->get_edges(), transform, true);
      return mesh;
    }

    Mesh *sphere(int vertical_count, int horizontal_count, float radius, float degrees) {
      auto points = new vec3[vertical_count];
      operations::circle_vertices(points, vertical_count, radius, M_PI);
      operations::transform(points, glm::eulerAngleX((float) M_PI_2), vertical_count);
      return operations::lathe(points, vertical_count, horizontal_count, degrees);
    }
  }
}