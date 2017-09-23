#include <SDL2/SDL.h>
#include "Controller_Manager.h"

namespace desktop {
  const auto INPUT_SUB_SYSTEMS = SDL_INIT_GAMECONTROLLER;

  Controller_Manager::Controller_Manager() {
    controller = NULL;
    SDL_InitSubSystem(INPUT_SUB_SYSTEMS);
  }

  Controller_Manager::~Controller_Manager() {
    if (controller) {
      SDL_GameControllerClose(controller);
      controller = NULL;
    }

    SDL_QuitSubSystem(INPUT_SUB_SYSTEMS);
  }

  SDL_GameController* find_controller() {
    auto count = SDL_NumJoysticks();
    if (count == 0)
      return NULL;

    for (int i = 0; i < count; ++i) {
      if (SDL_IsGameController(i)) {
        return SDL_GameControllerOpen(i);
      }
    }

    return NULL;
  }

  SDL_GameController * Controller_Manager::get_controller() {
    if (controller == NULL) {
      controller = find_controller();
      if (controller == NULL)
        return NULL;
    }

    if (SDL_GameControllerGetAttached(controller))
      return controller;

    return NULL;
  }
}