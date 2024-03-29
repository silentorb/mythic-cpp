
#ifndef Mythic_iOS_hpp
#define Mythic_iOS_hpp

#import <UIKit/UIKit.h>
#include "platforming/Platform_Factory.h"
#include <framing/Mutable_Frame.h>
#include <framing/Platform_Frame.h>
#include <memory>
#include "OpenGL_View.h"

using namespace std;

namespace clienting {
    class Mythic_Client;
}

namespace mythic {
    class Mythic_Engine;
}

namespace framing {
  class Platform_Frame;
};

class iOS_Frame : public framing::Mutable_Frame, public framing::Platform_Frame {

private:
    EAGLContext* context;
    OpenGL_View* view;
    int width, height;
    void create_window(const char *title, int width, int height);
    void create_gl_context();

public:
    iOS_Frame(EAGLContext* context, OpenGL_View* view, int width, int height);
    virtual void update_events();
    virtual void flip_buffer();
    virtual void release();
    virtual void initialize_window();
    virtual float get_pixel_scale() const override;
};

const string iOS_File_Loader(const string &path);
//class  iOS_Shader_Loader : public shading::Shader_Loader {
//public:
//    virtual string load(string path);
//};

void initialize_mythic_engine(mythic::Mythic_Engine & engine, platforming::Platform_Factory &factory);

class Mythic_iOS : public platforming::Platform_Factory {
    EAGLContext* context;
    unique_ptr<mythic::Mythic_Engine> engine;
OpenGL_View* view;
    
public:
    Mythic_iOS(EAGLContext* context, OpenGL_View* view, const lookinglass::Graphic_Options &graphic_options);
    virtual framing::Platform_Frame *create_frame(const lookinglass::Graphic_Options &graphic_options) override;
//    virtual shading::Shader_Loader *create_shader_loader() override;
    virtual haft::Input_Source *create_input_source(haft::Input_Configuration &config) override;
    virtual audio::Speaker *create_speaker() override;
    virtual platforming::Shader_Processor create_shader_processor() override;
    virtual platforming::File_Loader create_file_loader() override;
    virtual const string get_storage_path() override;

    void update(float delta);
};

#endif /* Mythic_iOS_hpp */
