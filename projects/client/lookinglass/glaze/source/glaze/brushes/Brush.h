#pragma once

#include "dllexport.h"
#include <functional>
#include <string>
#include "glaze/definition/Material.h"

using namespace std;

namespace glaze {
  namespace brushes {

    struct Donut {
        string vertex;
        string fragment;
    };
    typedef function<const Donut(const definition::Material &)> Brush;
  }
}