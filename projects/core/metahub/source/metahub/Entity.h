#pragma once

#include "Guid.h"

namespace metahub {

  struct Entity {
      Guid id;
      Guid trellis;
      unsigned char reference_count;
  };

}

