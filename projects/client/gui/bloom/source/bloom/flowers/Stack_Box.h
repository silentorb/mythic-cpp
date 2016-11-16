#pragma once

#include <bloom/layout/Measurement.h>
#include "Box.h"

namespace bloom {
  namespace flowers {

    class BLOOM_EXPORT Stack_Box : public Box {
        Parent *top;

    protected:
        void set_stack_bottom(Parent *first);
        void set_stack_top(Parent *top);

    public:
//        Stack_Box();
//        Stack_Box(Parent*first);
        virtual ~Stack_Box() {}

        virtual void clear() override;
        virtual void add_child(Flower *child) override;
        virtual void insert(Flower *child, int index) override;
        virtual void remove_child(Flower *child) override;

        virtual const string get_class_name() const override {
          return "Stack_Box";
        }
    };

  }
}