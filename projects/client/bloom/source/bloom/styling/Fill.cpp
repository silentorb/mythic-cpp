#include "Fill.h"
#include <drawing/Draw.h>

namespace bloom {

  void Fill::render(drawing::Draw &draw, const Bounds &bounds) const {
    draw.draw_square(bounds.get_position().x, bounds.get_position().y, bounds.get_dimensions().x,
                     bounds.get_dimensions().y, color, true);
  }
}