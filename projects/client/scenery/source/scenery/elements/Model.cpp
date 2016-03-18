#include "Model.h"
#include <glm/gtc/matrix_transform.hpp>
#include <lookinglass/Glass.h>
#include "texturing/Texture.h"

namespace scenery {

  Model::Model(Mesh_Data* mesh_data, Spatial_Effect *effect, Parent * parent)
    : mesh_data(mesh_data), effect(effect), Element(parent) {

  }

//  mat4 *Model::get_transform() {
//    tranform = glm::translate(glm::mat4(1.f), get_position());
//    return &tranform;
//  }

  void Model::render() {
    auto transform = get_transform();
//    auto transform = glm::translate(glm::mat4(1.f), get_position());
    auto normal_transform = get_absolute_orientation();
    if(texture)
      texture->activate();

    effect->activate(transform, normal_transform, opacity);

    Glass::get_instance().draw_mesh(*mesh_data, effect->get_draw_method());
  }
}
