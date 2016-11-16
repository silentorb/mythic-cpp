#include "Text_Button.h"

using namespace std;

namespace bloom {
  namespace widgetry {
    Text_Button::Text_Button(const string &content, flowers::Parent *parent) :
      Button_Container(parent) {
      initialize(content);
    }

    void Text_Button::initialize(const string &content) {
      text_layout = new flowers::Box_Group(padding);
      text = new flowers::Text(content, text_layout);
      text_layout->set_dimensions({Measurements::shrink, 0}, {Measurements::shrink, 0});
      text->set_size(16);
    }

  }
}