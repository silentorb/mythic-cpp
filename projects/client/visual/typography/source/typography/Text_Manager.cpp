#include "Text_Manager.h"
#include "texturing/initialize.h"
#include <ft2build.h>
#include FT_FREETYPE_H

using namespace resourceful;

namespace typography {

  struct Text_Manager_Internal {
      FT_Library library;
  };

  Text_Manager::Text_Manager(Shader_Manager &shader_manager, perspective::Viewport &viewport)
    : fonts(new Resource_Manager("fonts")),
      shader_manager(shader_manager),
      internal(new Text_Manager_Internal()) {
    texturing::initialize_texture_shaders(shader_manager);

    if (FT_Init_FreeType(&internal->library))
      throw runtime_error("Could not init FreeType Library");

    text_effect = unique_ptr<Text_Effect>(
      new Text_Effect(shader_manager.get_program("colored-image"), viewport));
  }

  Text_Manager::~Text_Manager() {
    FT_Done_FreeType(internal->library);
  }

  Font &Text_Manager::create_font(const string name, const string filename) {
    auto font = new Font(name, filename, &internal->library);
    fonts->add_resource(font);
    return *font;
  }

  Font &Text_Manager::get_font(const string &name) {
    for (auto it = fonts->begin(); it != fonts->end(); ++it) {
      auto font = (Font *) it->get();
      if (font->get_name() == name)
        return *font;
    }

    throw runtime_error("Could not find font: " + name + ".");
  }
}
