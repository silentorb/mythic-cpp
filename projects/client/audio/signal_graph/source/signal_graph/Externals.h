#pragma once

#include <functional>
#include <vector>
#include "External_Input.h"

namespace signal_graph {

  using Setter = std::function<void(void *)>;

//  class Externals {
//      std::vector<const void *> inputs;
//      std::vector<Setter> outputs;
//
//  public:
//      Externals(std::initializer_list<const void *> input_initializer,
//                std::initializer_list<Setter> output_initializer) :
//        inputs(input_initializer), outputs(output_initializer) {}
//
//      template<typename T>
//      const T &get_external(const External_Base &external) const {
//        return *(T *) inputs[external.get_index()];
//      }
//
//      template<typename T>
//      const T &get_input(const External_Input<T> &external) const {
//        return *(T *) inputs[external.get_index()];
//      }
//
//      template<typename T>
//      void set_output(const External_Output<T> &external, T value) {
//        outputs[external.get_index()](&value);
////        return *(T *) external_values[external.get_index()];
//      }
//  };
}
