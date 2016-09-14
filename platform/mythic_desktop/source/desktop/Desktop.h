#pragma once

#include "commoner/dllexport.h"
#include <memory>
#include "platforming/Platform_Factory.h"

using namespace std;
using namespace lookinglass;

namespace framing {
  class Platform_Frame;
}

namespace desktop {

  class MYTHIC_EXPORT Desktop : public platforming::Platform_Factory {
        const char *title;

  public:
       Desktop(const char *title);
     virtual const string get_storage_path() override;
      virtual platforming::Shader_Processor create_shader_processor() override;
      virtual platforming::File_Loader create_file_loader() override;
      virtual audio::Speaker *create_speaker() override;
      virtual framing::Platform_Frame *create_frame(const lookinglass::Graphic_Options &graphic_options) override;
      virtual haft::Input_Source *create_input_source(haft::Input_Configuration &config) override;

  };

}

