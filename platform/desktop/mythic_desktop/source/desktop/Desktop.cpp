#include <desktop/Desktop_Input.h>
#include <audio/Speaker.h>
#include "Desktop.h"
#include "desktop/Desktop_Frame.h"
#include "clienting/Mythic_Client.h"
#include <desktop_audio/interface.h>
#include <shading/shader_processing.h>
#include "Desktop_File_Loader.h"

using namespace lookinglass;

namespace desktop {

  Desktop::Desktop(const char *title) :
    title(title) {

  }

  framing::Platform_Frame *Desktop::create_frame(const lookinglass::Graphic_Options &graphic_options) {
    return new Desktop_Frame(title, graphic_options);
  }

//  shading::Shader_Loader *Desktop::create_shader_loader() {
//    return new Desktop_Shader_Loader("resources/shaders");
//  }

  haft::Input_Source *Desktop::create_input_source(haft::Input_Configuration &config) {
    return new Desktop_Input(config);
  }

  audio::Speaker *Desktop::create_speaker() {
    return desktop_create_speaker();
  }

  const char *get_resource_path() {
    return "resources";
  }

  platforming::Shader_Processor Desktop::create_shader_processor() {
    return [](shading::Shader_Type type, const string &source) {
      return source;
//      auto included = shading::process_includes(source, type, resourceful::File_Loader(Desktop_File_Loader));
//      return string("#version 150\nprecision highp float;\n\n") + shading::olden(included, type);
////      return string("#version 150\nprecision highp float;\n\n") + included;
//
////      return "#version 430\n" + shading::process_includes(source, type, resourceful::File_Loader(Desktop_File_Loader));
    };
  }

  platforming::File_Loader Desktop::create_file_loader() {
    return Desktop_File_Loader;
  }

  const string Desktop::get_storage_path() {
    return "";
  }

}

