#pragma once
#include "dllexport.h"

namespace timing {

  const double dt = 0.01;

  struct State {
      float x;
      float v;
  };

  struct Derivative {
      float dx;
      float dv;
  };

  class MYTHIC_EXPORT Quartz {
  public:
      Quartz(void);
      ~Quartz(void);

      float update(void);

  private:
      double get_delta(void);

      static float time();

      double t;

      double currentTime;
      double accumulator;

      State current;
      State previous;
  };

};
