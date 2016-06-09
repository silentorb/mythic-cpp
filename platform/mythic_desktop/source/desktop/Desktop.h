#pragma once

#include "dllexport.h"

#include <memory>
#include <mythic/Mythic_Engine.h>
#include "mythic/Platform_Factory.h"

using namespace std;
using namespace lookinglass;
using namespace mythic;

namespace desktop {

  class MYTHIC_EXPORT Desktop : public Platform_Factory {
  private:
      const char *title;
      unique_ptr<Mythic_Engine> engine;

  public:
      virtual mythic::Shader_Processor create_shader_processor() override;
      virtual mythic::File_Loader create_file_loader() override;
      virtual audio::Speaker *create_speaker() override;
      Desktop(const char *title, int width, int height);

      virtual Frame *create_frame(int width, int height) override;
//      virtual shading::Shader_Loader *create_shader_loader() override;
      virtual haft::Input_Source *create_input_source(haft::Input_Configuration &config) override;

      Mythic_Engine &get_engine() const {
        return *engine.get();
      }
  };

}

