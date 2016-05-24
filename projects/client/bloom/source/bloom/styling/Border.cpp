#include <bloom/Draw_Interface.h>
#include "Border.h"

namespace bloom {

  void Border::render(Draw_Interface &draw, const Bounds &bounds) const {
    draw.draw_square(bounds.get_position().x, bounds.get_position().y, bounds.get_dimensions().x,
                     bounds.get_dimensions().y, color, false);
  }
}