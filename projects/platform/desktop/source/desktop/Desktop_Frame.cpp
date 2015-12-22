#include "Desktop_Frame.h"
#include <iostream>
#include "SDL2/SDL.h"

namespace desktop {
  Desktop_Frame::Desktop_Frame(const char *title) {
    fullscreen = false;
        create_window(title, 800, 600);
  }

  void Desktop_Frame::create_window(const char *title, int width, int height) {
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

  void  Desktop_Frame::update() {
    SDL_Event event;
    if (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        std::cout << "Exiting program." << std::endl;
        closing = true;
        return;
      }
    }
  }

  int Desktop_Frame:: get_width(){
return 0;
  }

  int Desktop_Frame:: get_height(){
return 0;
  }
}