#pragma once

#include <string>
#include <vector>
#include <glaze/definition/Variable.h>

using namespace std;

namespace glaze {
  namespace rendering {

    const string declare_variables(const string &prefix, const vector<glaze::definition::Variable> &variables);
  }
}