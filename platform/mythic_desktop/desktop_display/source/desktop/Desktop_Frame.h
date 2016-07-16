#pragma once

#include "dllexport.h"
#include <framing/Mutable_Frame.h>
#include "framing/Platform_Frame.h"

struct SDL_Window;
namespace lookinglass {
  class Graphic_Options;
}
namespace desktop {

  class MYTHIC_EXPORT Desktop_Frame : public framing::Mutable_Frame, public framing::Platform_Frame {
      void *gl_context;
      void create_window(const char *title, const lookinglass::Graphic_Options &graphic_options);
      SDL_Window *sdl_window;
      void create_gl_context();
      using framing::Mutable_Frame::is_fullscreen;

  public:
      Desktop_Frame(const char *title, const lookinglass::Graphic_Options &graphic_options);

      virtual ~Desktop_Frame() { }

      virtual void update_events();
      virtual void flip_buffer();
      virtual void release() override;
      virtual void initialize_window() override;
  };
}

