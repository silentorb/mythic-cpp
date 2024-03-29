#pragma once


#include "Font.h"
#include "resourceful/Resource_Manager.h"
#include "Text_Effect.h"
#include <memory>
#include <shading/Shader_Manager.h>

using namespace std;
using namespace shading;

namespace typography {

  struct Text_Manager_Internal;

  class Text_Manager {
      unique_ptr<resourceful::Resource_Manager> fonts;
      Shader_Manager &shader_manager;
      unique_ptr<Text_Effect> text_effect;
      unique_ptr<Text_Manager_Internal> internal;

  public:
      Text_Manager(Shader_Manager &shader_manager,  perspective:: Viewport& viewport);

      ~Text_Manager();

      Font &create_font(const string name, const string filename);

      Font &get_font(const string &name);

      Text_Effect &get_text_effect() const {
        return *text_effect;
      }

  };
}

