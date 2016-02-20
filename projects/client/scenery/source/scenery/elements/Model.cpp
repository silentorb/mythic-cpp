#include "Model.h"
#include <glm/gtc/matrix_transform.hpp>

namespace scenery {
  Model::Model(Mesh_Data* mesh_data, Spatial_Effect *effect, Parent & parent)
    : mesh_data(mesh_data), effect(effect), Element(parent) {

  }

//  mat4 *Model::get_transform() {
//    tranform = glm::translate(glm::mat4(1.f), get_position());
//    return &tranform;
//  }

  void Model::render(Glass &glass) {
    auto transform = get_transform();
//    auto transform = glm::translate(glm::mat4(1.f), get_position());
    effect->activate(transform);

    glass.draw_mesh(*mesh_data, effect->get_draw_method());
  }
}
