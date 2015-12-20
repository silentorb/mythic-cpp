#pragma once

#include <string>

using namespace std;

struct SDL_Window;

namespace lookinglass {
  class Glass {
  public:

      Glass(const char *title);

      virtual ~Glass() { }

  private:
      void create_window(const char* title);
      SDL_Window *sdl_window;
      void* gl_context;

      int width;
      int height;
      bool fullscreen;
  };

}

