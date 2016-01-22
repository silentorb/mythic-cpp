#pragma once

#include "dllexport.h"
#include "Font.h"
#include "resourceful/Resource_Manager.h"
#include <memory>
#include <shading/Shader_Manager.h>
#include <shading/effects/Color_Effect.h>

using namespace std;
using namespace shading;

namespace typography {
  class MYTHIC_EXPORT Font_Manager {
      unique_ptr<resourceful::Resource_Manager> fonts;
      FT_Library library;
      Shader_Manager &shader_manager;
      unique_ptr<Color_Effect> text_effect;

  public:
      Font_Manager(Shader_Manager &shader_manager);
      ~Font_Manager();
      Font &create_font(const string name, const string filename);
      Font &get_font(const string &name);


      Color_Effect &get_text_effect() const {
        return *text_effect;
      }
  };
}

