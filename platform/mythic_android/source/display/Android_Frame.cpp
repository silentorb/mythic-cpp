#include "Android_Frame.h"
#include "lookinglass/glow.h"
#include <dlfcn.h>
#include <stdexcept>
#include "logger.h"

Android_Frame::Android_Frame(Android_App *app)
  : app(app), window(app->window) {

  initialize_window();
  load_gl_functions();
}

void Android_Frame::initialize_window() {
  const EGLint attribs[] = {
    EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
    EGL_CONFORMANT, EGL_OPENGL_ES2_BIT,
    EGL_BLUE_SIZE, 8,
    EGL_GREEN_SIZE, 8,
    EGL_RED_SIZE, 8,
    EGL_DEPTH_SIZE, 16,
    EGL_NONE
  };
  EGLint dummy, format;
  EGLint numConfigs;
  EGLConfig config;

  display = eglGetDisplay(EGL_DEFAULT_DISPLAY);

  log_info("initializing display");
  eglInitialize(display, 0, 0);

  /* Here, the application chooses the configuration it desires. In this
   * sample, we have a very simplified selection process, where we pick
   * the first EGLConfig that matches our criteria */
  eglChooseConfig(display, attribs, &config, 1, &numConfigs);

  /* EGL_NATIVE_VISUAL_ID is an attribute of the EGLConfig that is
   * guaranteed to be accepted by ANativeWindow_setBuffersGeometry().
   * As soon as we picked a EGLConfig, we can safely reconfigure the
   * ANativeWindow buffers to match, using EGL_NATIVE_VISUAL_ID. */
  eglGetConfigAttrib(display, config, EGL_NATIVE_VISUAL_ID, &format);
  log_info("creating geometry buffers");
  ANativeWindow_setBuffersGeometry(app->window, 0, 0, format);
  log_info("creating surface");
  surface = eglCreateWindowSurface(display, config, app->window, NULL);

  EGLint context_attributes[] = {
    EGL_CONTEXT_CLIENT_VERSION, 2,
    EGL_NONE
  };
  log_info("creating_context");
  context = eglCreateContext(display, config, NULL, context_attributes);

  if (eglMakeCurrent(display, surface, surface, context) == EGL_FALSE) {
    log_info("eglMakeCurrent1");
    glow::check_error("Unable to eglMakeCurrent");
    log_info("ceglMakeCurrent2");
//    throw std::runtime_error("Unable to eglMakeCurrent");
  }

  eglQuerySurface(display, surface, EGL_WIDTH, &width);
  eglQuerySurface(display, surface, EGL_HEIGHT, &height);
  set_dimensions(width, height);
  log_info("Screen dimensions: %d, %d", width, height);
}

void Android_Frame::update_events() {
  int ident;
  int events;
  struct android_poll_source *source;

  while ((ident = ALooper_pollAll(0, NULL, &events,
                                  (void **) &source)) >= 0) {

    if (source != NULL) {
      source->process(app, source);
    }

    if (app->destroyRequested != 0) {
//      log_info("Abandon All Mythic.");
      closing = true;
      return;
    }
  }
}

void Android_Frame::flip_buffer() {
  eglSwapBuffers(display, surface);
}

void Android_Frame::load_gl_functions() {
  void *library = dlopen("libGLESv2.so", RTLD_LAZY);
  glGenVertexArrays = (PFNGLGENVERTEXARRAYSOESPROC) dlsym(library, "glGenVertexArraysOES");
  glBindVertexArray = (PFNGLBINDVERTEXARRAYOESPROC) dlsym(library, "glBindVertexArrayOES");
}

void Android_Frame::free() {
  if (display != EGL_NO_DISPLAY) {
    eglMakeCurrent(display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
    if (context != EGL_NO_CONTEXT) {
      eglDestroyContext(display, context);
    }
    if (surface != EGL_NO_SURFACE) {
      eglDestroySurface(display, surface);
    }
    eglTerminate(display);
  }

  display = EGL_NO_DISPLAY;
  context = EGL_NO_CONTEXT;
  surface = EGL_NO_SURFACE;

}