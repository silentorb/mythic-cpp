#include "general.h"

namespace glaze {
  namespace rendering {


    const string declare_variables(const string &prefix, const vector<glaze::definition::Variable> &variables) {
      string result;
      for (auto &variable: variables) {
        result += prefix + variable.get_type().get_name() + " " + variable.get_name() + ";\n";
      }
      return result;
    }


  }
}