#pragma once

#include "dllexport.h"
#include "Font.h"
#include "resourceful/Resource_Manager.h"
#include <memory>
#include <lookinglass/shading/Shader_Manager.h>

using namespace std;
using namespace lookinglass::shading;

namespace typography {
  class MYTHIC_EXPORT Font_Manager {
      unique_ptr<resourceful::Resource_Manager> fonts;
      FT_Library library;
      Shader_Manager &shader_manager;

  public:
      Font_Manager(Shader_Manager &shader_manager);
      ~Font_Manager();
      Font &create_font(const char *filename);
  };
}

