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

      class To_dB : public Node {
      public:
          Input<float> input;
          Output<float> output;

          To_dB_Data() :
            input(this),
            output(this) {

          }

          To_dB(Node *input_source) : To_dB_Data() {
            input.set_other_property(input_source);
          }

          virtual ~To_dB() {

          }

          virtual void update(const Stroke &stroke, void *raw_data) override {
            auto &data = *(To_dB_Data *) raw_data;
            data.output = std::pow(data.input, 2);
          }
      };
    }
  }
}