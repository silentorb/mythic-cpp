#pragma once

#include "dllexport.h"
#include "aura/Speaker.h"
#include <SDL2/SDL_audio.h>

//using namespace std;

namespace desktop {

  class MYTHIC_EXPORT Desktop_Speaker : public aura::Speaker {

      SDL_AudioDeviceID device;

  public:
      virtual void start() override;
      virtual void stop() override;
  };
}