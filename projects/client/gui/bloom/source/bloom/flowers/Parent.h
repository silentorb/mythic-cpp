#pragma once

#include "Flower.h"

namespace bloom {
  namespace flowers {

    class Parent : public virtual Flower {
    public:
        virtual void add_child(Flower *child) = 0;
        virtual void insert(Flower *child, int index) = 0;
        virtual void remove_child(Flower *child) = 0;
        virtual void clear() = 0;
    };

  }
}