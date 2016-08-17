#pragma once

#include "Node.h"
#include <aura/graphing/nodes/Add.h>
#include <aura/graphing/nodes/Multiply.h>

namespace aura {
  namespace graphing {

    nodes::Add *operator+(Node &first, Node &second) {
      return new nodes::Add(&first, &second);
    }

    nodes::Multiply *operator*(Node &first, Node &second) {
      return new nodes::Multiply(&first, &second);
    }
  }
}