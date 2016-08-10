#pragma once

#include <aura/graphing/Node.h>

namespace aura {
  namespace graphing {
    namespace nodes {

      template<typename T>
      class AURA_EXPORT Constant : public Node {
          Constant_Output <T> output;

      public:
          Constant(T value) : output(value, this) {}

          virtual void update(const Stroke &stroke, void *raw_data) override {

          }
      };
    }
  }
}