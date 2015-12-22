#pragma once

#include "lookinglass/Frame.h"

struct SDL_Window;
namespace desktop {
  class Desktop_Frame : public lookinglass::Frame {

  private:
      void *gl_context;
      void create_window(const char *title, int width, int height);
      SDL_Window *sdl_window;
      void create_gl_context();

  public:
      Desktop_Frame(const char *title);
      virtual void update();
      virtual int get_width();
      virtual int get_height();
      virtual void flip_buffer();
      virtual void set_clear_color(float red, float green, float blue, float alpha);
      virtual void clear();
  };
}

