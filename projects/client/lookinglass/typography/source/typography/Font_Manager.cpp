#include "Font_Manager.h"

using namespace resourceful;

namespace typography {
  Font_Manager::Font_Manager(Shader_Manager &shader_manager)
    : fonts(new Resource_Manager("fonts")),
      shader_manager(shader_manager) {

    if (FT_Init_FreeType(&library))
      throw runtime_error("Could not init FreeType Library");

    auto &program = shader_manager.create_program("text",
                                  shader_manager.create_shader(Shader_Type::vertex,
                                                               "typography/text.vertex"),
                                  shader_manager.create_shader(Shader_Type::fragment,
                                                               "typography/text.fragment"));

    text_effect = unique_ptr<Color_Effect>(new Color_Effect(program));
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
