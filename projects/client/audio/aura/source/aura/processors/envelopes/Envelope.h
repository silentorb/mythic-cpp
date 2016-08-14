#pragma once

#include "commoner/dllexport.h"
#include "Curve.h"
#include <vector>
using namespace std;

namespace aura {

  class MYTHIC_EXPORT Envelope {
      vector <Curve> curves;

  public:
      Envelope(initializer_list<Curve>initializer);
  };
}