#include "Material.h"

namespace glaze {
  namespace definition {

    void Material::add_inputs(initializer_list<Variable> initializer) {
      for(auto & variable: initializer){
        inputs.push_back(variable);
      }
    }

    void Material::add_uniforms(initializer_list<Variable> initializer) {
      for(auto & variable: initializer){
        uniforms.push_back(variable);
      }
    }
  }
}