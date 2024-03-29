#pragma once

#include "House.h"
#include <shading/Shader_Processor.h>
#include <resourceful/File_Loader.h>

namespace lookinglass {

  class Lookinglass_House : public House {
  public:
      Lookinglass_House(framing::Platform_Frame *frame, resourceful::File_Loader file_loader,
                        shading::Shader_Processor shader_processor, const Graphic_Options &options);

  };
}