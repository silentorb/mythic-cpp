#include "Model.h"

  namespace scenery {
    namespace elements {
      Model::Model(Mesh_Data& mesh, shared_ptr<Spatial_Effect> effect)
        : mesh(mesh), effect(effect) {

      }

      mat4 *Model::get_transform() {
				return nullptr;
      }

      void Model::render(Glass &glass) {
        effect->activate(*get_transform());

        glass.draw_mesh(mesh,effect->get_draw_method());
      }

    }
  }
