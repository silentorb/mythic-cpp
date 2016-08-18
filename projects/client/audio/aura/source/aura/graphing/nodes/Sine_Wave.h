#pragma once

#include <aura/graphing/Node.h>
#include <cmath>
#include <math/utility.h>

namespace aura {
  namespace graphing {
    namespace nodes {

      AURA_EXPORT Node Sine_Wave_With_Position_Source(const Node &position_source);
      AURA_EXPORT Node Sine_Wave(const Node &frequency);

//      class Sine_Wave : public Node {
//      public:
//          Input<float> position;
//          Output<float> output;
//
//          Sine_Wave() :
//            position(this),
//            output(this), Node(<#initializer#>) {
//
//          }
//
//          virtual ~Sine_Wave() {
//
//          }
//
//          Sine_Wave(Node *position_source) : Sine_Wave(), Node(<#initializer#>) {
//            position.set_other_property(position_source);
//          }
//
////          Sine_Wave(const Engineer &engineer, Node *frequency_source);
//
//          virtual void update(const Stroke &stroke, void *raw_data) override {
//            auto &data = *(Sine_Wave_Data *) raw_data;
//            data.output = sin(data.position * 2 * Pi);
//          }
//      };
    }
  }
}