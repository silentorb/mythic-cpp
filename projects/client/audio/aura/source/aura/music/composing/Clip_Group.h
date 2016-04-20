#pragma once

#include "dllexport.h"
#include "Clip.h"
#include <vector>
#include <memory>

using namespace std;

namespace aura {

  class MYTHIC_EXPORT Clip_Group {
      vector<unique_ptr<Clip>> clips;
  };
}