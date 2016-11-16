#include <bloom/flowers/Fill.h>
#include "Button_Container.h"
#include <glm/vec3.hpp>

using namespace glm;

namespace bloom {
  namespace widgetry {

    Button_Container::Button_Container(flowers::Parent *parent) :
      flowers::Box_Group(parent) {
      initialize();
    }

    void Button_Container::initialize() {
      insert(new flowers::Fill(vec4(vec3(0.1f), 1)), 0);
      interactive = new flowers::Interactive_Template<1>(&Events::activate);
      add_child(interactive);
      padding = new flowers::Box_Group(this);
      padding->set_margins(20);
      padding->set_dimensions({Measurements::shrink, 0}, {Measurements::shrink, 0});
      border = new flowers::Border(vec4(0.9, 0.9, 0.9, 1), 3, this);
      set_dimensions({Measurements::shrink, 0}, {Measurements::shrink, 0});
    }

    void Button_Container::click(const Delegate &action) {
      interactive->on(Events::activate, [action, this](const Event &event) {
        if (interactive->is_inside(event))
          action();
      });
    }
  }
}