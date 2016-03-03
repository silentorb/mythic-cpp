#pragma once

#include "Flower.h"
#include <string>

using namespace std;

namespace bloom {

  class Text_Flower;

  class MYTHIC_EXPORT Button : public Flower {
Text_Flower*text;

  public:
      Button(string text_content, Garden &garden, Flower &parent);
  };
}