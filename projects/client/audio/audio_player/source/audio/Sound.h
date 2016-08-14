#pragma once
#include "commoner/dllexport.h"
#include "Waveform.h"

namespace audio {

  struct MYTHIC_EXPORT Sound {
      Waveform & waveform;
      float position;
  };
}