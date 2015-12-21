#pragma once

#include "Frame.h"

struct SDL_Window;
namespace lookinglass {
  class Desktop_Frame : public Frame {
  public:
      Desktop_Frame(const char *title);
      virtual void update();

  private:
      void create_window(const char *title);
      SDL_Window *sdl_window;
  };

}

