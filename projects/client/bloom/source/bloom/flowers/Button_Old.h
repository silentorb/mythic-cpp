#pragma once

#include "Flower_Old.h"
#include <string>

using namespace std;

namespace bloom {

  class Text_Flower;

  class MYTHIC_EXPORT Button_Old : public Flower_Old {

  protected:
      Text_Flower *text;

  public:
      Button_Old(string text_content, Flower_Old *parent);
      void set_text(string content);

      void set_font_size(int size);
  };
}