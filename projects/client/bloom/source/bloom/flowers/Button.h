#pragma once

#include "Flower.h"
#include <string>

using namespace std;

namespace bloom {

  class Text_Flower;

  class MYTHIC_EXPORT Button : public Flower {

  protected:
      Text_Flower *text;

  public:
      Button(string text_content, Flower *parent);
      void set_text(string content);

      void set_font_size(int size);
  };
}