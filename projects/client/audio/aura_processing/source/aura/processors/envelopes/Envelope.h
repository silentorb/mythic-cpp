#pragma once


#include "Curve.h"
#include <vector>
using namespace std;

namespace aura {

  class Envelope {
      vector <Curve> curves;

  public:
      Envelope(initializer_list<Curve>initializer);
  };
}