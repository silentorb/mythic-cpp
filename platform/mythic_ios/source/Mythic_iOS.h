
#ifndef Mythic_iOS_hpp
#define Mythic_iOS_hpp

#import <UIKit/UIKit.h>
#include "mythic/Platform_Factory.h"
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

namespace framing {
  class Platform_Frame;
};

class iOS_Frame : public framing::Platform_Frame {

private:
    EAGLContext* context;
    int width, height;
    void create_window(const char *title, int width, int height);
    void create_gl_context();

public:
    iOS_Frame(EAGLContext* context, int width, int height);
    virtual void update_events();
    virtual void flip_buffer();
    virtual void free();
    virtual void initialize_window();
};

const string iOS_File_Loader(const string &path);
//class  iOS_Shader_Loader : public shading::Shader_Loader {
//public:
//    virtual string load(string path);
//};

void initialize_mythic_engine(mythic::Mythic_Engine & engine);

class Mythic_iOS : public mythic::Platform_Factory {
    EAGLContext* context;
    unique_ptr<mythic::Mythic_Engine> engine;

public:
    Mythic_iOS(EAGLContext* context);
    virtual framing::Platform_Frame *create_frame(int width, int height) override;
//    virtual shading::Shader_Loader *create_shader_loader() override;
    virtual haft::Input_Source *create_input_source(haft::Input_Configuration &config) override;
    virtual audio::Speaker *create_speaker() override;
    virtual mythic::Shader_Processor create_shader_processor() override;
    virtual mythic::File_Loader create_file_loader() override;
    virtual const string get_storage_path() override;

    void update();
};

#endif /* Mythic_iOS_hpp */
