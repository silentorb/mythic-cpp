#pragma once

#include <aura/graphing/Node.h>
#include <cmath>
#include <math/utility.h>

namespace aura {
  namespace graphing {
    namespace nodes {

      struct Sine_Wave_Data {
          float position;
          float output;
      };

      class Sine_Wave : public Node {
      public:
          Input<float> position;
          Output<float> output;

          Sine_Wave() :
            position(this),
            output(this) {

          }

          virtual ~Sine_Wave() {

          }

          Sine_Wave(Output<float> &position_source): Sine_Wave() {
            position.set_other_property(&position_source);
          }

          virtual void update(const Stroke &stroke, void *raw_data) override {
            auto &data = *(Sine_Wave_Data *) raw_data;
            data.output = sin(data.position * 2 * Pi);
          }
      };
    }
  }
}