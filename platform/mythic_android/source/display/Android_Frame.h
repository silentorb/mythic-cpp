#pragma once

#include "lookinglass/Frame.h"
#include <EGL/egl.h>
#include "android_native_app_glue.h"

class Android_Frame : public lookinglass::Frame {
private:
    ANativeWindow *window;
    EGLDisplay display;
    EGLSurface surface;
    EGLContext context;
    EGLint width, height;
    android_app *app;

    void load_gl_functions();
public:

    Android_Frame(android_app *app);
    virtual void update_events();
//    virtual int get_width();
//    virtual int get_height();
    virtual void flip_buffer();
    void free();
    void initialize_window();
};