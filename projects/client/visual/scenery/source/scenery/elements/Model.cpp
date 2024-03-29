#include "Model.h"
#include <glm/gtc/matrix_transform.hpp>
#include <lookinglass/Glass.h>
#include <glow.h>
#include "texturing/Texture.h"
#include <scenery/Complex_Spatial_Effect.h>

namespace scenery {

  Model::Model(Renderable_Mesh_With_Opacity *mesh_data, Complex_Spatial_Effect *effect)
    : mesh_data(mesh_data), effect(effect), Simple_Element() {
//    if (mesh_data->get_ebo() == 0)
//      throw runtime_error("Model mesh is not initialized.");
  }

  void Model::render() {
    render(parent->get_spatial());
  }

  void Model::render(Spatial_Source &spatial_old) {
    auto &transform = spatial_old.get_transform();
    auto &normal_transform = spatial_old.get_absolute_orientation();
    if (texture)
      texture->activate();

//    effect->prepare(mesh_data, transform, normal_transform, color.w != 1 || mesh_data->has_opacity(), color);
  }
}
