#include "Model.h"
#include <glm/gtc/matrix_transform.hpp>
#include <lookinglass/Glass.h>
#include <lookinglass/glow.h>
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

    effect->activate(transform, normal_transform, opacity != 1 || mesh_data->has_opacity());
//    if (opacity != 1 || mesh_data->has_opacity()) {
//      glow::set_culling(false);
//      glow::set_blend(true);
//    }
//    else {
//      glow::set_culling(true);
//      glow::set_blend(false);
//    }

//    Glass::get_instance().draw_mesh(*mesh_data, effect->get_draw_method());
    mesh_data->draw(effect->get_draw_method());
  }
}
