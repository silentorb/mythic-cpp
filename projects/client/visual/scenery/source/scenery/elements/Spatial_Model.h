#pragma once

#include "Spatial.h"
#include "Model.h"

namespace scenery {

  class MYTHIC_EXPORT Spatial_Model : public Spatial {
  protected:
      Model model;

  public:
      Spatial_Model(Mesh_Data *mesh_data, Complex_Spatial_Effect *effect, Parent *parent = nullptr);
      ~Spatial_Model() {}

      Model &get_model() {
        return model;
      }

      virtual void render() override;
  };
}