
#ifndef Mythic_iOS_hpp
#define Mythic_iOS_hpp

#import <UIKit/UIKit.h>
#include "mythic/Platform_Factory.h"
#include "lookinglass/Frame.h"
#include "shading/Shader_Loader.h"
#include <memory>

using namespace std;

using namespace lookinglass;

namespace clienting {
    class Client;
}

namespace mythic {
    class Mythic_Engine;
    class Platform_Factory;
}

class iOS_Frame : public Frame {

private:
    EAGLContext* context;
    int width, height;
    void create_window(const char *title, int width, int height);
    void create_gl_context();

public:
    iOS_Frame(EAGLContext* context, int width, int height);
    virtual void update_events();
    virtual int get_width();
    virtual int get_height();
    virtual void flip_buffer();
    virtual void free();
    virtual void initialize_window();
};

class  iOS_Shader_Loader : public shading::Shader_Loader {
public:
    virtual string load(string path);
};

void initialize_mythic_engine(mythic::Mythic_Engine & engine);

class Mythic_iOS : public mythic::Platform_Factory {
    EAGLContext* context;
    unique_ptr<mythic::Mythic_Engine> engine;

public:
    Mythic_iOS(EAGLContext* context);
    virtual lookinglass::Frame *create_frame() override;
    virtual shading::Shader_Loader *create_shader_loader() override;
    virtual haft::Input_Source *create_input_source(haft::Input_Configuration &config) override;

    void update();
};

#endif /* Mythic_iOS_hpp */
