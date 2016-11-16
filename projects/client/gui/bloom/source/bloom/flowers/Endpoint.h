#pragma once

#include "Flower.h"

namespace bloom {
  namespace flowers {

    class Endpoint : public virtual Flower {
    public:
        virtual int get_child_count() override {
          return 0;
        }

        virtual Flower *get_child(int index) override {
          return nullptr;
        }

        virtual const string get_class_name() const override {
          return "Endpoint";
        }
    };
  }
}