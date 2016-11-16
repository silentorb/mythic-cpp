#pragma once

#include <bloom/flowers/Text.h>
#include "Button_Container.h"

namespace bloom {
  namespace widgetry {

    class Text_Button : public Button_Container {
        flowers::Text *text;

    protected:
        flowers::Box_Group *text_layout;
        void initialize(const string &content);

    public:
        Text_Button(const  std::string &content, flowers::Parent *parent = nullptr);

        virtual ~Text_Button() {}

        void set_content(const std::string &content) {
          text->set_content(content);
        }

        flowers::Text *get_text() const {
          return text;
        }

        virtual const string get_class_name() const override;
    };
  }
}