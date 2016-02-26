
#include "Mythic_iOS.h"
#include "lookinglass/House.h"
#include "clienting/Client.h"
#include "mythic/Mythic_Engine.h"
#include "laboratory/Lab.h"
#include "lookinglass/glow.h"
#include "iOS_Input.h"

using namespace laboratory;

string iOS_Shader_Loader::load(string path) {
    NSString *formatted_path = [[[NSBundle mainBundle] resourcePath]
                                stringByAppendingString:[NSString stringWithUTF8String:("/shaders/" + path + ".glsl").c_str()]];
//    NSBundle * b =[NSBundle mainBundle];
//    NSString *resource_path = [[NSBundle mainBundle] pathForResource:@"solid.fragment.glsl"  ofType:nil];
    NSError *error = nil;
    NSString *content = [NSString stringWithContentsOfFile:formatted_path
                                                  encoding:NSASCIIStringEncoding
                                                     error:&error];

    if (content == nil)
        throw std::runtime_error("Could not open file \"" + path + "\"");

//    BOOL fileExists = [[NSFileManager defaultManager] fileExistsAtPath:formatted_path];
//    NSLog(@"\n%lu\n%@",(unsigned long)NSASCIIStringEncoding,error);
    return std::string([content UTF8String]);
}

iOS_Frame::iOS_Frame(EAGLContext* context, int width, int height)
    :context(context), width(width), height(height) {

}

void iOS_Frame::create_window(const char *title, int width, int height) {

}

//void iOS_Frame::create_gl_context() {
//
//    glFrontFace(GL_CW);
//    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//}

void  iOS_Frame::update_events() {
//    SDL_Event event;
//    if (SDL_PollEvent(&event)) {
//        if (event.type == SDL_QUIT) {
//            std::cout << "Exiting program." << std::endl;
//            closing = true;
//            return;
//        }
//    }
}

int iOS_Frame::get_width() {
  CGRect screenBounds = [[UIScreen mainScreen] bounds];
  CGFloat screenScale = [[UIScreen mainScreen] scale];
  CGSize pixels = CGSizeMake(screenBounds.size.width * screenScale, screenBounds.size.height * screenScale);
    return pixels.width;
}

int iOS_Frame::get_height() {
  CGRect screenBounds = [[UIScreen mainScreen] bounds];
  CGFloat screenScale = [[UIScreen mainScreen] scale];
  CGSize pixels = CGSizeMake(screenBounds.size.width * screenScale, screenBounds.size.height * screenScale);
    return pixels.height;
}

void iOS_Frame::flip_buffer() {
//    SDL_GL_SwapWindow(sdl_window);
    [context presentRenderbuffer:GL_RENDERBUFFER];
}

// void iOS_Frame::set_clear_color(float red, float green, float blue, float alpha) {
//     glClearColor(red, green, blue, alpha);
// }
//
// void iOS_Frame::clear() {
//     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
// }

void iOS_Frame::free() {

}

void iOS_Frame::initialize_window() {

}

Mythic_iOS::Mythic_iOS(EAGLContext* context):context(context) {
    
    try {

     engine=unique_ptr<Mythic_Engine>{new Mythic_Engine(*this)};

    engine->get_client().load();
        
        initialize_mythic_engine(*engine);
    }
    catch(std::exception ex) {
        @throw [NSException exceptionWithName:@"Mythic Error"
                                       reason:[NSString stringWithUTF8String:ex.what()] userInfo:nil];
    }
    catch(char const* message) {
        @throw [NSException exceptionWithName:@"Mythic Error"
                                       reason:[NSString stringWithUTF8String:message] userInfo:nil];
    }
    catch(...) {
        @throw [NSException exceptionWithName:@"Mythic Error"
                                       reason:@"Unknown" userInfo:nil];
    }
}

Frame *Mythic_iOS::create_frame() {
    return new iOS_Frame(context, 0, 0);
}

haft::Input_Source *Mythic_iOS::create_input_source(haft::Input_Configuration & config) {
    return new iOS_Input(config);
}

shading::Shader_Loader *Mythic_iOS::create_shader_loader() {
    return new iOS_Shader_Loader();
}

void Mythic_iOS::update() {
    engine->update();
}
