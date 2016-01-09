#include <lookinglass/Renderable.h>
#include <vectoring/utility.h>
#include "House.h"
#include "lookinglass/glow.h"
#include "lookinglass/Glass.h"
#include "lookinglass/glow/Capabilities.h"
#include "lookinglass/glow/Version.h"
#include "lookinglass/shading/Shader_Manager.h"
#include "lookinglass/perspective/Viewport.h"
#include "lookinglass/through/create_mist.h"

namespace lookinglass {
  House::House(Frame *frame, Shader_Loader *shader_loader) :
    frame(frame) {
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

    shader_manager = unique_ptr<Shader_Manager>(new Shader_Manager(shader_loader, *capabilities));
    auto scene_definition = new Struct_Info(1, "", {
      new Field_Info("view", Field_Type::matrix),
      new Field_Info("projection", Field_Type::matrix),
      new Field_Info("camera_direction", Field_Type::vector3)
    });
    viewport_mist = unique_ptr<Mist<Viewport_Data>>(
      through::create_mist<Viewport_Data>(scene_definition, get_capabilities()));
    shader_manager->add_program_add_listener(*viewport_mist);
    base_viewport = unique_ptr<Viewport>(new Viewport(*viewport_mist, frame->get_width(), frame->get_height()));
    base_viewport->activate();
    glass = unique_ptr<Glass>(new Glass(get_capabilities(), get_base_viewport()));

    glFrontFace(GL_CW);
    glDisable(GL_CULL_FACE);

    glClearColor(0, 0.1f, 0.3f, 1);
  }

  House::~House() {
  }

  void House::update() {
    frame->update_events();
    frame->clear();

    base_viewport->update_device();

    for (auto renderable : renderables) {
      renderable->render(*glass);
    }

    frame->flip_buffer();
  }

  bool House::is_closing() {
    return frame->closing;
  }

  void House::add_renderable(Renderable *renderable) {
    renderables.push_back(renderable);
  }

  void House::remove_renderable(Renderable *renderable) {
    vector_remove(renderables, renderable);
  }
}