#pragma once

#include "dllexport.h"
#include "Font.h"
#include "resourceful/Resource_Manager.h"
#include "Text_Effect.h"
#include <memory>
#include <shading/Shader_Manager.h>

using namespace std;
using namespace shading;

namespace typography {

  class MYTHIC_EXPORT Text_Manager {
      unique_ptr<resourceful::Resource_Manager> fonts;
      FT_Library library;
      Shader_Manager &shader_manager;
      unique_ptr<Text_Effect> text_effect;

  public:
      Text_Manager(Shader_Manager &shader_manager, const ivec2 &viewport_dimensions);

      ~Text_Manager();

      Font &create_font(const string name, const string filename);

      Font &get_font(const string &name);

      Text_Effect &get_text_effect() const {
        return *text_effect;
      }

  };
}

