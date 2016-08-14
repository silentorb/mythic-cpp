#pragma once

#include "commoner/dllexport.h"
#include "audio/Speaker.h"
#include <SDL2/SDL_audio.h>

//using namespace std;

namespace desktop {

  class MYTHIC_EXPORT Desktop_Speaker : public audio::Speaker {

      SDL_AudioDeviceID device;
      SDL_AudioSpec have;

  public:
      virtual audio::Device_Settings start() override;
      virtual void stop() override;

  };
}