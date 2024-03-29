#include "Lookinglass_Resources.h"
#include <glow/Capabilities.h>
#include "shading/Shader_Manager.h"
#include "texturing/Texture.h"
#include "resourceful/Resource_Manager.h"
#include "typography/Text_Manager.h"
#include "modeling/Mesh_Data.h"

using namespace resourceful;
using namespace typography;
using namespace shading;
using namespace modeling;

namespace lookinglass {

  Lookinglass_Resources::Lookinglass_Resources(resourceful::File_Loader file_loader,
                                               shading::Shader_Processor shader_processor,
                                               perspective::Viewport &viewport) :
    general(new Resource_Manager("general")),
    texture_manager(new Resource_Manager("textures")),
    mesh_manager(new Resource_Manager("meshes")) {

    shader_manager = unique_ptr<Shader_Manager>(new Shader_Manager(file_loader, shader_processor));
    text_manager = unique_ptr<Text_Manager>(new Text_Manager(*shader_manager, viewport));
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

  void Lookinglass_Resources::release() {
    mesh_manager->release();
    shader_manager->release();
  }

  void Lookinglass_Resources::add_texture(texturing::Texture *texture) {
    texture_manager->add_resource(texture);
  }

  void Lookinglass_Resources::add_mesh(Mesh_Data *data) {
    mesh_manager->add_resource(data);
  }

  void Lookinglass_Resources::add_mesh(std::unique_ptr<Mesh_Data> data) {
    mesh_manager->add_resource(std::move(data));
  }

  void Lookinglass_Resources::add_font(const string name, const string path) {
    text_manager->create_font(name, path);
  }

  Font &Lookinglass_Resources::get_font(const string name) {
    return text_manager->get_font(name);
  }

  typography::Text_Effect &Lookinglass_Resources::get_text_effect() const {
    return text_manager->get_text_effect();
  }

  void Lookinglass_Resources::add_resource(resourceful::Resource *resource) {
    general->add_resource(resource);
  }

  void Lookinglass_Resources::remove_resource(resourceful::Resource *resource) {
    general->remove_resource(resource);
  }
}