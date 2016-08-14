#pragma once

#include "commoner/dllexport.h"

#include <memory>
#include <mythic/Mythic_Engine.h>
#include "mythic/Platform_Factory.h"

using namespace std;
using namespace lookinglass;
using namespace mythic;

namespace framing {
  class Platform_Frame;
}

namespace desktop {

  class MYTHIC_EXPORT Desktop : public Platform_Factory {
  private:
      const char *title;
      unique_ptr<Mythic_Engine> engine;

  public:
      virtual const string get_storage_path() override;
      virtual mythic::Shader_Processor create_shader_processor() override;
      virtual mythic::File_Loader create_file_loader() override;
      virtual audio::Speaker *create_speaker() override;
      Desktop(const char *title, const lookinglass::Graphic_Options &graphic_options);

      virtual framing::Platform_Frame *create_frame(const lookinglass::Graphic_Options &graphic_options) override;
//      virtual shading::Shader_Loader *create_shader_loader() override;
      virtual haft::Input_Source *create_input_source(haft::Input_Configuration &config) override;

      Mythic_Engine &get_engine() const {
        return *engine.get();
      }
  };

}

