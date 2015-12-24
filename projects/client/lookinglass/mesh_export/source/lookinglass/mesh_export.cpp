#include "mesh_export.h"

namespace lookinglass {
  namespace mesh_export {
    Mesh_Data *ooutput_textured(Mesh &mesh) {
      auto result = new Mesh_Data();

      for(auto polygon: mesh.polygons){
        for (int i = 0; i < polygon->vertices.size(); ++i) {

        }
      }
    }
  }
}
