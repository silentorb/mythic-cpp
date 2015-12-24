#include <lookinglass/Renderable.h>
#include <vectoring/utility.h>
#include "House.h"
#include "lookinglass/glow.h"
#include "lookinglass/Glass.h"
#include "lookinglass/glow/Capabilities.h"
#include "lookinglass/glow/Version.h"

namespace lookinglass {
  House::House(Frame &frame) :
    frame(frame) {

    auto version = glow::Version();
    capabilities = new glow::Capabilities(version);
    glass = new Glass(*capabilities);
    frame.set_clear_color(0, 0.1f, 0.3f, 1);
  }

  House::~House() {
    delete glass;
    delete capabilities;
  }

  void House::update() {
    frame.update_events();
    frame.clear();

    for (auto renderable: renderables) {
      renderable->render(*glass);
    }

    frame.flip_buffer();
  }

  bool House::is_closing() {
    return frame.closing;
  }

  void House::add_renderable(Renderable *renderable) {
    renderables.push_back(renderable);
  }

  void House::remove_renderable(Renderable *renderable) {
    vector_remove(renderables, renderable);
  }
}