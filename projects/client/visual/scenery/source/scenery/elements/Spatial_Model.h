#pragma once

#include "Spatial.h"
#include "Model.h"

namespace scenery {

  class Spatial_Model : public Spatial {
  protected:
      Model model;

  public:
      Spatial_Model(Renderable_Mesh_With_Opacity *mesh_data, Complex_Spatial_Effect *effect);
      ~Spatial_Model() {}

      Model &get_model() {
        return model;
      }

      void set_mesh(Renderable_Mesh_With_Opacity *mesh_data){
        model.set_mesh(mesh_data);
      }

      virtual void render() override;
  };
}