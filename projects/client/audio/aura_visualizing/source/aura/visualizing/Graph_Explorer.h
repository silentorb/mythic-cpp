#pragma once

#include <bloom/flowers/Box_Group.h>
#include <bloom/flowers/List.h>

namespace aura {
  namespace visualizing {

    class Graph_Explorer : public bloom::flowers::Box_Group {
        bloom::flowers::List *list;
    };
  }
}