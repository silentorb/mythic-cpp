#include "Lookinglass_House.h"
#include <lookinglass/Renderable.h>
#include <vectoring/utility.h>
#include <resourceful/Resource_Handler.h>
#include "House.h"
#include "glow.h"
#include "glow/Capabilities.h"
#include "perspective/Viewport.h"
#include "through/create_mist.h"
#include "Lookinglass_Resources.h"
#include "shading/Shader_Manager.h"
#include "lookinglass/Renderable_List.h"
#include "typography/Text_Effect.h"
#include "framing/Platform_Frame.h"
#include "glow_gl.h"

using namespace resourceful;

namespace lookinglass {

  House *House::instance = nullptr;

  House::House(framing::Platform_Frame *frame, const Graphic_Options &options) :
    frame(frame),
    options(options),
    resource_handler(new Resource_Handler()) {
    instance = this;
    renderable = []() {};
  }

  House::~House() {

  }

  void House::set_renderable(const Renderable &renderable) {
    this->renderable = renderable;
  }

  void House::update() {
    if (!active)
      return;

    frame->update_events();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    auto viewport = Viewport::get_active_viewport();
    viewport->set_dimensions(frame->get_dimensions());
    viewport->update_device();

    renderable();

    frame->flip_buffer();
  }

  bool House::is_closing() {
    return frame->is_closing();
  }

  Lookinglass_Resources &House::get_resources() const {
    return *resource_manager;
  }

  framing::Frame_Info &House::get_frame() const {
    return *frame;
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

  void House::release() {
    viewport_mist->release();
    resource_manager->release();
    frame->release();
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

  void House::watch_resource(const std::shared_ptr<resourceful::Resource> &resource) {
    resource_handler->add_resource(resource);
  }

  const Version &House::get_version() const {
    return capabilities->get_version();
  }

  glow::Capabilities &House::get_capabilities() const {
    return *capabilities;
  }

  texturing::buffering::Frame_Buffer &House::get_frame_buffer() const {
    return *frame_buffer;
  }
}