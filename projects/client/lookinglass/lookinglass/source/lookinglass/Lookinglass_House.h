#pragma once

#include "House.h"
#include <shading/Shader_Loader.h>
#include <resourceful/File_Loader.h>

namespace lookinglass {

  class MYTHIC_EXPORT Lookinglass_House : public House {
  public:
      Lookinglass_House(Frame *frame, resourceful::File_Loader file_loader, shading::Shader_Processor shader_processor);

  };
}