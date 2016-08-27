#include "Desktop_Frame.h"
#include <iostream>
#include <stdexcept>
#include "SDL2/SDL.h"
#include "glow.h"
#include "lookinglass/Graphic_Options.h"
#include "glow_gl.h"

namespace desktop {
  Desktop_Frame::Desktop_Frame(const char *title, const lookinglass::Graphic_Options &graphic_options) {
    set_fullscreen(false);
    create_window(title, graphic_options);
    create_gl_context();
  }

  void Desktop_Frame::create_window(const char *title, const lookinglass::Graphic_Options &graphic_options) {
    set_dimensions(graphic_options.get_width(), graphic_options.get_height());
    SDL_Init(SDL_INIT_VIDEO);   // Initialize SDL2
    int fullscreen_flag = is_fullscreen() ? SDL_WINDOW_FULLSCREEN : SDL_WINDOW_RESIZABLE;

    if(graphic_options.get_multisampling()) {
      SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
      SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, graphic_options.get_multisampling());
    }

    sdl_window = SDL_CreateWindow(
      title,
      SDL_WINDOWPOS_UNDEFINED,           //    initial x position
      SDL_WINDOWPOS_UNDEFINED,           //    initial y position
      graphic_options.get_width(),
      graphic_options.get_height(),
      SDL_WINDOW_OPENGL | fullscreen_flag | SDL_WINDOW_SHOWN
    );

    // Check that the window was successfully made
    if (sdl_window == NULL) {
      // In the event that the window could not be made...
      std::cout << "Could not create window: " << SDL_GetError() << '\n';
      throw std::runtime_error("Could not create window.");
    }
  }

  void Desktop_Frame::create_gl_context() {
    gl_context = SDL_GL_CreateContext(sdl_window);
    if (!gl_context) {
      auto error = SDL_GetError();
      throw error;
    }

    //    glbinding::Binding::initialize(false);
    if (!glow::initialize_desktop()) {
      SDL_GL_DeleteContext(gl_context);
      throw std::runtime_error("Could not load OpenGL functions.");
    }
//		glFrontFace(GL_CW);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  }

  void  Desktop_Frame::update_events() {
    SDL_Event event;
    if (SDL_PollEvent(&event)) {

      switch (event.type) {
        case SDL_QUIT:
          std::cout << "Exiting program." << std::endl;
          closing = true;
          return;

//        case SDL_WINDOWEVENT_SIZE_CHANGED:
        case SDL_WINDOWEVENT:
          switch (event.window.event) {
            case SDL_WINDOWEVENT_SIZE_CHANGED:
              std::cout << "Window Dimensions: " <<
              std::to_string(event.window.data1) << ", " <<
              std::to_string(event.window.data2) << std::endl;

              set_dimensions(
                event.window.data1,
                event.window.data2
              );
          }
      }

    }
  }

  void Desktop_Frame::flip_buffer() {
    SDL_GL_SwapWindow(sdl_window);
  }

  void Desktop_Frame::release() {

  }

  void Desktop_Frame::initialize_window() {

  }

}