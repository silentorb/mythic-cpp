#include "Spatial_Model.h"

namespace scenery {

  Spatial_Model::Spatial_Model(Mesh_Data *mesh_data, Complex_Spatial_Effect *effect, Parent *parent) :
    Spatial(parent), model(mesh_data, effect) {
  }

  void Spatial_Model::render() {
    Simple_Element::render();
    model.render(*this);
  }
}