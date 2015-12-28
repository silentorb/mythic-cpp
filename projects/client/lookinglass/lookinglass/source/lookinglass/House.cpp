#include <lookinglass/Renderable.h>
#include <vectoring/utility.h>
#include "House.h"
#include "lookinglass/glow.h"
#include "lookinglass/Glass.h"
#include "lookinglass/glow/Capabilities.h"
#include "lookinglass/glow/Version.h"
#include "lookinglass/shading/Shader_Manager.h"

namespace lookinglass {
  House::House(Frame *frame, Shader_Loader *shader_loader) :
    frame(frame),
    shader_manager(new Shader_Manager(shader_loader)),
    capabilities(new glow::Capabilities(glow::Version())),
    glass(new Glass(*capabilities)) {

    frame->set_clear_color(0, 0.1f, 0.3f, 1);
  }

  House::House(Platform_Factory &factory) : House(factory.create_frame(), factory.create_shader_loader()) { }

  House::~House() {
  }

  void House::update() {
    frame->update_events();
    frame->clear();

    for (auto renderable: renderables) {
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