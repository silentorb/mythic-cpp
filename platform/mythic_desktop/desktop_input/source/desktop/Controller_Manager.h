#pragma once

#include <SDL2/SDL_gamecontroller.h>
#include "dllexport.h"

namespace desktop {

  class MYTHIC_EXPORT Controller_Manager {
  private:
      SDL_GameController *controller;

  public:
      ~Controller_Manager();
      Controller_Manager();
      SDL_GameController * get_controller();
  };
}