#pragma once

#include "commoner/dllexport.h"
#include "Variable.h"
#include <vector>

using namespace std;

namespace glaze {
namespace definition {
  class MYTHIC_EXPORT Material {
      vector<Variable> inputs;
      vector<Variable> uniforms;

  public:

      Material() { }

      Material(initializer_list<Material *> mixins) { }
      void add_inputs(initializer_list<Variable>initializer);
      void add_uniforms(initializer_list<Variable>initializer);

      const vector<Variable> &get_inputs() const {
        return inputs;
      }

      const vector<Variable> &get_uniforms() const {
        return uniforms;
      }
  };
}
}