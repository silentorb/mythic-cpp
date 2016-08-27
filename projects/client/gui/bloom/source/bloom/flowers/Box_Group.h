#pragma once

#include <bloom/layout/Measurement.h>
#include "Box.h"
#include "Stack_Box.h"

namespace bloom {
  namespace flowers {

    class Group;

    class BLOOM_EXPORT Box_Group : public Stack_Box {

    public:
        Box_Group(Parent *parent = nullptr);

        virtual ~Box_Group() {}
    };

  }
}