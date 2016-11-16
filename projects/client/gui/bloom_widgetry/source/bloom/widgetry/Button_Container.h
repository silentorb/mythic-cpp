#pragma once

#include <bloom/flowers/Box_Group.h>
#include <bloom/flowers/Interactive.h>
#include <bloom/flowers/Border.h>
#include <bloom/flowers/Interactive_Template.h>

namespace bloom {
  namespace widgetry {

    class Button_Container:public flowers:: Box_Group {
    protected:
        flowers::Interactive_Template_Inside<1> *interactive;
        flowers::Border *border;
        flowers::Box_Group *padding;

        void initialize();

    public:
        Button_Container(flowers::Parent *parent = nullptr);

        virtual ~Button_Container() {}

        virtual void click(const Delegate &action);

        void set_border(glm::vec4 color) {
          border->set_color(color);
        }

        void set_border(glm::vec4 color, int size) {
          border->set_color(color);
          border->set_size(size);
        }

        flowers::Box_Group *get_padding() const {
          return padding;
        }
    };
  }
}