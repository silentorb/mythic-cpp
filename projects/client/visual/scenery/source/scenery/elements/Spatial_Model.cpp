#include "Spatial_Model.h"

namespace scenery {

  Spatial_Model::Spatial_Model(Renderable_Mesh_With_Opacity *mesh_data, Complex_Spatial_Effect *effect) :
    Spatial(), model(mesh_data, effect) {
  }

  void Spatial_Model::render() {
    Simple_Element::render();
    model.render(*this);
  }
}