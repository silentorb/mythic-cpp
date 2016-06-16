#pragma once

#include "Flower.h"

namespace bloom {
  namespace flowers {

    class Parent;

    class BLOOM_EXPORT Child : public virtual Flower {
        friend class Parent;

    protected:
        Parent *parent = nullptr;

    public:
        Child(Parent *parent);

        Parent *get_parent() const {
          return parent;
        }

    };
  }
}