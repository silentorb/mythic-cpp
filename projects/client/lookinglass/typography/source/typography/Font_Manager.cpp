#include "Font_Manager.h"

using namespace resourceful;

namespace typography {
  Font_Manager::Font_Manager(Shader_Manager &shader_manager)
    : fonts(new Resource_Manager("fonts")),
      shader_manager(shader_manager) {

    if (FT_Init_FreeType(&library))
      throw runtime_error("Could not init FreeType Library");

    text_effect = unique_ptr<Text_Effect>(new Text_Effect(shader_manager.get_program("colored-image")));
  }

  Font_Manager::~Font_Manager() {
    FT_Done_FreeType(library);
  }

  Font &Font_Manager::create_font(const string name, const string filename) {
    auto font = new Font(name, filename, library);
    fonts->add_resource(font);
    return *font;
  }

  Font &Font_Manager::get_font(const string &name) {
    for (auto it = fonts->begin(); it != fonts->end(); ++it) {
      auto font = (Font *) it->get();
      if (font->get_name() == name)
        return *font;
    }

    throw runtime_error("Could not find font: " + name + ".");
  }
}
