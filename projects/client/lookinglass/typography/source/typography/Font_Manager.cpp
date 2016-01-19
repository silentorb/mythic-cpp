#include "Font_Manager.h"

using namespace resourceful;

namespace typography {
  Font_Manager::Font_Manager(Shader_Manager &shader_manager)
    : fonts(new Resource_Manager("fonts")),
      shader_manager(shader_manager) {

    if (FT_Init_FreeType(&library))
      throw runtime_error("Could not init FreeType Library");

    shader_manager.create_program("text",
                                  shader_manager.create_shader(Shader_Type::vertex,
                                                               "typography/text.vertex"),
                                  shader_manager.create_shader(Shader_Type::fragment,
                                                               "typography/text.fragment"));
  }

  Font_Manager::~Font_Manager() {
    FT_Done_FreeType(library);
  }

  Font &Font_Manager::create_font(const char *filename) {
    auto font = new Font(filename, library);
    fonts->add_resource(font);
    return *font;
  }
}
