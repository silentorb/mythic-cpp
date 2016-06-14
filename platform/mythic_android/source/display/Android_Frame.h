#pragma once

#include <EGL/egl.h>
#include "android_native_app_glue.h"
#include <framing/Mutable_Frame.h>
#include "framing/Platform_Frame.h"

class Android_Frame : public framing::Mutable_Frame, public framing::Platform_Frame {
private:
    ANativeWindow *window;
    EGLDisplay display;
    EGLSurface surface;
    EGLContext context;
    EGLint width, height;
    Android_App *app;

    void load_gl_functions();
public:

    Android_Frame(Android_App *app);

    virtual ~Android_Frame() { }

    virtual void update_events();
//    virtual int get_width();
//    virtual int get_height();
    virtual void flip_buffer();
    void free();
    void initialize_window();
};