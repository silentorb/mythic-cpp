#pragma once

#include <bloom/flowers/Box_Group.h>
#include <glm/vec4.hpp>
#include <bloom/flowers/Interactive_Template.h>

namespace bloom {
  namespace widgetry {

    class Slider : public flowers::Box_Group {
        flowers::Box_Group *left_side;
        flowers::Box_Group *right_side;
        flowers::Box_Group *knob;
        float value = 0.5f;
        float knob_offset = 0;
        flowers::Interactive_Template<2> *interactive;
        std::function<void(float value)> changed_delegate;

        flowers::Box_Group *create_side(glm::vec4 color, flowers::Parent *parent);
        void initialize_layout();
        void initialize_interaction();
        void update_user_input();

    public:
        Slider();

        void set_value(float new_value);

        float get_value() const {
          return value;
        }

        void on_changed(const function<void(float)> &value) {
          changed_delegate = value;
        }
    };
  }
}