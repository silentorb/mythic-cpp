#pragma once


#include <functional>
#include <string>

using namespace std;

namespace audio {
  class Speaker;
}
namespace haft {
  class Input_Source;

  class Input_Configuration;
}

namespace shading {
  enum class Shader_Type : unsigned int;
}

namespace framing {
  class Platform_Frame;
};

namespace lookinglass {
  class Graphic_Options;
}

namespace platforming {

  typedef function<const string(const string &)> File_Loader;
  typedef function<const string(shading::Shader_Type, const string &)> Shader_Processor;

  class Platform_Factory {

  public:
      virtual framing::Platform_Frame *create_frame(const lookinglass::Graphic_Options &graphic_options) = 0;
      virtual haft::Input_Source *create_input_source(haft::Input_Configuration &config) = 0;
      virtual audio::Speaker *create_speaker() = 0;
      virtual Shader_Processor create_shader_processor() = 0;
      virtual File_Loader create_file_loader() = 0;
      virtual const string get_storage_path() = 0;
  };


}
