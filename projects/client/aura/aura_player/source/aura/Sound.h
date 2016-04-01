#pragma once
#include "dllexport.h"
#include "Waveform.h"

namespace aura {

  struct MYTHIC_EXPORT Sound {
      Waveform & waveform;
      float position;
  };
}