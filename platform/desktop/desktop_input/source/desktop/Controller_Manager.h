#pragma once

#include <SDL2/SDL_gamecontroller.h>

namespace desktop {

  class Controller_Manager {
  private:
      SDL_GameController *controller;

  public:
      ~Controller_Manager();
      Controller_Manager();
      SDL_GameController * get_controller();
  };
}