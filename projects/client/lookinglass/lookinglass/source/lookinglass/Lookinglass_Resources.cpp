#include "Lookinglass_Resources.h"
#include <lookinglass/glow/Capabilities.h>
#include "shading/Shader_Manager.h"
#include "texturing/Texture.h"
#include "resourceful/Resource_Manager.h"
#include "typography/Font_Manager.h"
#include "modeling/Mesh_Data.h"

using namespace resourceful;
using namespace typography;
using namespace shading;
using namespace modeling;

namespace lookinglass {

  Lookinglass_Resources::Lookinglass_Resources(Shader_Loader *shader_loader, glow::Capabilities &capabilities) :
    texture_manager(new Resource_Manager("textures")),
    mesh_manager(new Resource_Manager("meshes")) {

    shader_manager = unique_ptr<Shader_Manager>(new Shader_Manager(shader_loader, capabilities));
    Font_Manager m(*shader_manager);
    font_manager = unique_ptr<Font_Manager>(new Font_Manager(*shader_manager));
  }

  Lookinglass_Resources::~Lookinglass_Resources() {

  }

  shading::Shader_Manager &Lookinglass_Resources::get_shader_manager() const {
    return *shader_manager;
  }

  void Lookinglass_Resources::load() {
    mesh_manager->load();
    shader_manager->load();
  }

  void Lookinglass_Resources::free() {
    mesh_manager->free();
    shader_manager->free();
  }

  void Lookinglass_Resources::add_texture(texturing::Texture *texture) {
    texture_manager->add_resource(texture);
  }

  void Lookinglass_Resources::add_mesh(Mesh_Data *data) {
    mesh_manager->add_resource(data);
  }

  void Lookinglass_Resources::add_font(const string name, const string path) {
    font_manager->create_font(name, path);
  }

  Font &Lookinglass_Resources::get_font(const string name) {
    return font_manager->get_font(name);
  }

  typography::Text_Effect &Lookinglass_Resources::get_text_effect() const {
    return font_manager->get_text_effect();
  }
}