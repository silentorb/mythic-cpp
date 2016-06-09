#pragma once

#include "dllexport.h"
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
////  class Shader_Loader;
//  class Shader_Processor;
  enum class Shader_Type : unsigned int;
}

namespace lookinglass {

  class Frame;
};
using namespace lookinglass;

namespace mythic {

  typedef function<const string(const string &)> File_Loader;
  typedef function<const string(shading::Shader_Type, const string &)>  Shader_Processor;

  class MYTHIC_EXPORT Platform_Factory {

  public:
      virtual Frame *create_frame(int width, int height) = 0;
//      virtual shading::Shader_Loader *create_shader_processor() = 0;
      virtual haft::Input_Source *create_input_source(haft::Input_Configuration &config) = 0;
      virtual audio::Speaker *create_speaker() = 0;
      virtual Shader_Processor create_shader_processor()= 0;
      virtual File_Loader create_file_loader() = 0;
  };


}
