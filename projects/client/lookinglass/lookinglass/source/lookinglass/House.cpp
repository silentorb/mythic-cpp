#include <lookinglass/Renderable.h>
#include <vectoring/utility.h>
#include "House.h"
#include "lookinglass/glow.h"
#include "lookinglass/glow/Capabilities.h"
#include "lookinglass/perspective/Viewport.h"
#include "lookinglass/through/create_mist.h"
#include "Lookinglass_Resources.h"
#include "shading/Shader_Manager.h"
#include "lookinglass/Renderable_List.h"
#include "typography/Text_Effect.h"

using namespace resourceful;

namespace lookinglass {
  House::House(Frame *frame, Shader_Loader *shader_loader) :
    frame(frame), renderables(new Renderable_List()) {
    if (!frame) {
      throw std::runtime_error("Frame (Window) was null.");
    }
#define GL2_0
#ifdef GL2_0
    auto version = glow::Version(2, 0);
#else
    auto version = glow::Version();
#endif
    capabilities = unique_ptr<Capabilities>(new glow::Capabilities(version));

    resource_manager = unique_ptr<Lookinglass_Resources>(
      new Lookinglass_Resources(shader_loader, *capabilities, ivec2(frame->get_width(), frame->get_height())));
    auto scene_definition = new Struct_Info(1, "", {
      new Field_Info("view", Field_Type::matrix),
      new Field_Info("projection", Field_Type::matrix),
      new Field_Info("camera_direction", Field_Type::vector3)
    });
    viewport_mist = unique_ptr<Mist<Viewport_Data>>(
      through::create_mist<Viewport_Data>(scene_definition, get_capabilities()));
    resource_manager->get_shader_manager().add_program_add_listener(*viewport_mist);
    base_viewport = unique_ptr<Viewport>(new Viewport(*viewport_mist, frame->get_width(), frame->get_height()));
    base_viewport->activate();
    base_viewport->add_listener(Vector2_Delegate(
      [&](const ivec2 &dimensions) { resource_manager->get_text_effect().set_viewport_dimensions(dimensions); }));

    glass = unique_ptr<Glass>(new Glass(get_capabilities(), get_base_viewport()));
    initialize();
  }

  House::~House() {
  }

  void House::update() {
    if (!active)
      return;

    frame->update_events();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    base_viewport->set_dimensions(frame->get_dimensions());
    base_viewport->update_device();

    renderables->render(*glass);

    frame->flip_buffer();
  }

  bool House::is_closing() {
    return frame->closing;
  }

  void House::add_renderable(Renderable &renderable) {
    renderables->add(renderable);
  }

  void House::remove_renderable(Renderable &renderable) {
    renderables->remove(renderable);
  }

  Lookinglass_Resources &House::get_resources() const {
    return *resource_manager;
  }

  void House::initialize() {
    glFrontFace(GL_CCW);
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);

//    glClearColor(0, 0.1f, 0.3f, 1);
    glClearColor(1, 1, 1, 1);
  }

  void House::load() {
    frame->initialize_window();
    initialize();
    resource_manager->load();
    set_active(true);
  }

  void House::free() {
    viewport_mist->free();
    resource_manager->free();
    frame->free();
    set_active(false);
  }

  shading::Shader_Manager &House::get_shader_manager() const {
    return resource_manager->get_shader_manager();
  }
}