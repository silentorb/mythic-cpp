#pragma once

#include "dllexport.h"
#include "lookinglass/Frame.h"

struct SDL_Window;

namespace desktop {

  class MYTHIC_EXPORT Desktop_Frame : public lookinglass::Frame {
      void *gl_context;
      void create_window(const char *title, int width, int height);
      SDL_Window *sdl_window;
      void create_gl_context();

  public:
      Desktop_Frame(const char *title, int width, int height);
      virtual void update_events();
      virtual void flip_buffer();
      virtual void free() override;
      virtual void initialize_window() override;
  };
}

