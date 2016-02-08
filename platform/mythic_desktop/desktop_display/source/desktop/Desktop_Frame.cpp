#include "Desktop_Frame.h"
#include <iostream>
#include <stdexcept>
#include "SDL2/SDL.h"
#include "lookinglass/glow.h"

namespace desktop {
	Desktop_Frame::Desktop_Frame(const char *title) {
		fullscreen = false;
		create_window(title, 800, 600);
		create_gl_context();
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
#if _MSC_VER
		if (!gladLoadGL()) {
			SDL_GL_DeleteContext(gl_context);
			throw std::runtime_error("Could not load OpenGL functions.");
		}
#else
		if (ogl_LoadFunctions() == ogl_LOAD_FAILED) {
			SDL_GL_DeleteContext(gl_context);
			throw std::runtime_error("Could not load OpenGL functions.");
		}
#endif
		glFrontFace(GL_CW);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	void  Desktop_Frame::update_events() {
		SDL_Event event;
		if (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				std::cout << "Exiting program." << std::endl;
				closing = true;
				return;
			}
		}
	}

	int Desktop_Frame::get_width() {
		return 800;
	}

	int Desktop_Frame::get_height() {
		return 600;
	}

	void Desktop_Frame::flip_buffer() {
		SDL_GL_SwapWindow(sdl_window);
	}

	void Desktop_Frame::free() {

	}

	void Desktop_Frame::initialize_window() {

	}
}