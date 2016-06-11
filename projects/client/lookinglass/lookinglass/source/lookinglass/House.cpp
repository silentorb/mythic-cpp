#include "Lookinglass_House.h"
#include <lookinglass/Renderable.h>
#include <vectoring/utility.h>
#include "House.h"
#include "lookinglass/glow.h"
#include "lookinglass/glow/Capabilities.h"
#include "perspective/Viewport.h"
#include "lookinglass/through/create_mist.h"
#include "Lookinglass_Resources.h"
#include "shading/Shader_Manager.h"
#include "lookinglass/Renderable_List.h"
#include "typography/Text_Effect.h"

using namespace resourceful;

namespace lookinglass {

  House *House::instance = nullptr;

  House::House(framing::Frame *frame) :
    frame(frame) {
    instance = this;
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

    for (auto &renderable : renderables) {
      renderable();
    }

    frame->flip_buffer();
  }

  bool House::is_closing() {
    return frame->closing;
  }

  void House::add_renderable(Renderable renderable) {
    renderables.push_back(renderable);
  }

//  void House::remove_renderable(Renderable &renderable) {
//    renderables->remove(renderable);
//  }

  Lookinglass_Resources &House::get_resources() const {
    return *resource_manager;
  }

  void House::initialize() {
    glFrontFace(GL_CCW);
    glow::set_depth_test(true);

#ifdef GL_PROGRAM_POINT_SIZE
    glEnable(GL_PROGRAM_POINT_SIZE);
    glEnable(0x8861);  // GL_POINT_SPRITE
#else
    // glEnable(0x8861);
#endif

    //    glClearColor(0, 0.1f, 0.3f, 1);
    glClearColor(1, 1, 1, 1);
  }

  void House::load() {
//    frame->initialize_window();
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

  const glm::ivec2 &House::get_dimensions() {
    return base_viewport->get_dimensions();
  }

  House &House::get_instance() {
    return *instance;
  }
}