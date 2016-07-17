#include "Model.h"
#include <glm/gtc/matrix_transform.hpp>
#include <lookinglass/Glass.h>
#include <lookinglass/glow.h>
#include "texturing/Texture.h"

namespace scenery {

  Model::Model(Mesh_Data *mesh_data, Spatial_Effect *effect, Parent *parent)
    : mesh_data(mesh_data), effect(effect), Element(parent) {

  }

  void Model::render() {
    auto transform = get_transform();
    auto normal_transform = get_absolute_orientation();
    if (texture)
      texture->activate();

    effect->render(mesh_data, transform, normal_transform, opacity != 1 || mesh_data->has_opacity(), opacity);
  }
}
