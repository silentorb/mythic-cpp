#include "Model.h"

namespace lookinglass {
  namespace scenery {
    namespace elements {
      Model::Model(unsigned int mesh_id, shared_ptr<Spatial_Effect *> effect)
        : mesh_id(mesh_id), effect(effect) {

      }

      mat4 *Model::get_transform() {

      }

      void Model::render(Glass &glass) {
        (*effect)->activate(*get_transform());

        glass.draw_mesh(mesh_id,(*effect)->get_draw_method());
      }

    }
  }
}