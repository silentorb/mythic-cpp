#include "Text.h"
#include "shading/effects/Color_Effect.h"

namespace typography {
  Text::Text(Font &font, shading::Color_Effect &effect, const string &content) : font(font), effect(effect),
  content(content) { }
}