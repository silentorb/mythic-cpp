#pragma once

#include <aura/graphing/Node.h>
#include <cmath>

namespace aura {
  namespace graphing {
    namespace nodes {

      struct To_dB_Data {
          float input;
          float output;
      };

      Node To_dB(const Node & source) {
        return Node(
          NODE_ID("To_dB")
          {
            new Input<float>(source),
            new Output<float>(),
          },
          [](const Stroke &stroke, void *raw_data) {
            auto &data = *(To_dB_Data *) raw_data;
            data.output = std::pow(data.input, 2);
          });
      }

      Node To_dB() {
        return To_dB(Node::create_empty());
      }
//      class To_dB : public Node {
//      public:
//          Input<float> input;
//          Output<float> output;
//
//          To_dB_Data() :
//            input(this),
//            output(this) {
//
//          }
//
//          To_dB(Node *input_source) : To_dB_Data(), Node(<#initializer#>) {
//            input.set_other_property(input_source);
//          }
//
//          virtual ~To_dB() {
//
//          }
//
//          virtual void update(const Stroke &stroke, void *raw_data) override {
//            auto &data = *(To_dB_Data *) raw_data;
//            data.output = std::pow(data.input, 2);
//          }
//      };
    }
  }
}