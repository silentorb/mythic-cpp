#include "lookinglass/Glass.h"
#include "SDL2/SDL.h"
#include <iostream>

namespace lookinglass {

  Glass::Glass(const char *title) {
    fullscreen = false;
    width = 800;
    height = 600;
    create_window(title);
  }

  void Glass::create_window(const char *title) {
    SDL_Init(SDL_INIT_VIDEO);   // Initialize SDL2
    int fullscreen_flag = fullscreen ? SDL_WINDOW_FULLSCREEN : SDL_WINDOW_RESIZABLE;
    sdl_window = SDL_CreateWindow(
      title,
      SDL_WINDOWPOS_UNDEFINED,           //    initial x position
      SDL_WINDOWPOS_UNDEFINED,           //    initial y position
      width,
      height,
      SDL_WINDOW_OPENGL | fullscreen_flag | SDL_WINDOW_SHOWN
    );

    // Check that the window was successfully made
    if (sdl_window == NULL) {
      // In the event that the window could not be made...
      std::cout << "Could not create window: " << SDL_GetError() << '\n';
      throw "Could not create window.";
    }
  }
}