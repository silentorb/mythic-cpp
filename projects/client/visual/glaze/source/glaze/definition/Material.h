#pragma once


#include "Variable.h"
#include <vector>

using namespace std;

namespace glaze {
namespace definition {
  class Material {
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