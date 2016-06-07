#pragma once
#include "dllexport.h"
#include <functional>
#include <string>
#include "glaze/definition/Material.h"

using namespace std;

namespace glaze {
  namespace brushes {

    typedef function<const string(const definition::Material &)> Brush;
  }
}