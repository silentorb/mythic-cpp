#include "Model.h"
#include <glm/gtc/matrix_transform.hpp>
#include <lookinglass/Glass.h>
#include <lookinglass/glow.h>
#include "texturing/Texture.h"
#include <scenery/Spatial_Effect.h>

namespace scenery {

  Model::Model(Mesh_Data *mesh_data, Spatial_Effect *effect, Parent *parent)
    : mesh_data(mesh_data), effect(effect), Simple_Element(parent) {
    if (mesh_data->get_ebo() == 0)
      throw runtime_error("Model mesh is not initialized.");
  }

  void Model::render() {
    render(parent->get_spatial());
  }

  void Model::render(Spatial_Source &spatial) {
    auto &transform = spatial.get_transform();
    auto &normal_transform = spatial.get_absolute_orientation();
    if (texture)
      texture->activate();

    effect->render(mesh_data, transform, normal_transform, color.w != 1 || mesh_data->has_opacity(), color);
  }
}
