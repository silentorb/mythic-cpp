#include "Model.h"
#include <glm/gtc/matrix_transform.hpp>

namespace scenery {
  namespace elements {
    Model::Model(shared_ptr<Mesh_Data> mesh_data, shared_ptr<Spatial_Effect> effect)
      : mesh_data(mesh_data), effect(effect) {

    }

    mat4 *Model::get_transform() {
      tranform = glm::translate(glm::mat4(1.f), get_position());
      return &tranform;
    }

    void Model::render(Glass &glass) {
      effect->activate(*get_transform());

      glass.draw_mesh(*mesh_data, effect->get_draw_method());
    }
  }
}
